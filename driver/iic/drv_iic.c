#include "drv_iic.h"
#include "drv_systick.h"



void drv_iic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void drv_sda_in(void)
{
 	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
 	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7; 
 	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void drv_sda_out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void drv_iic_start(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_out();					  //将数据线设置为输出

	GPIO_SetBits(GPIOB, GPIO_Pin_7);  //在时钟线拉高前拉高数据线，以免检测到上升沿
	GPIO_SetBits(GPIOB,GPIO_Pin_6);   //拉高时钟线
	drv_systick_delay_us(5);  		  //时序要求大于4.7us
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//拉低数据线，产生下降沿
	drv_systick_delay_us(5);		  //时序要求大于4us

	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线占用iic总线，仲裁原则：时钟线低电平优先原则
}
void drv_iic_stop(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_out();					  //将数据线设置为输出

	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//拉低数据线
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	  //拉高时钟线
	drv_systick_delay_us(5); 		  //时序要求大于4us
	GPIO_SetBits(GPIOB, GPIO_Pin_7);  //拉高数据线
	drv_systick_delay_us(5);		  //时序要求大于4.7us

	//GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线（传输结束无需占用iic总线）
}
void drv_iic_sendACK(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_out();					  //将数据线设置为输出

	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//拉低数据线
	GPIO_SetBits(GPIOB,GPIO_Pin_6);   //拉高时钟线
	drv_systick_delay_us(5);		  //时序要求大于4us
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线占用iic总线
	//GPIO_SetBits(GPIOB, GPIO_Pin_7);

}
void drv_iic_sendNOACK(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_out();					  //将数据线设置为输出
	
	GPIO_SetBits(GPIOB, GPIO_Pin_7);  //拉高数据线
	GPIO_SetBits(GPIOB,GPIO_Pin_6);   //拉高时钟线
	drv_systick_delay_us(5);		  //时序要求大于4us
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线占用iic总线
}

//把时钟线拉高，读取数据线上的数据：高电平（非应答）、低电平（应答）
u8 drv_iic_waitACK(void)
{
	u16 time_out=0;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_in();					  //将数据线设置为输入

	GPIO_SetBits(GPIOB, GPIO_Pin_6);  //拉高数据线
	//等待数据传入,应答时结束循环
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)){
		time_out++;
		if(time_out > 300){
			drv_iic_stop();
			return NOACK;
		}
	}
	return ACK;
}
void drv_iic_sendbyte(u8 data)
{
	u8 i;
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_out();					  //将数据线设置为输出
	//当时钟线为高时，数据线上的数据不能发生改变（稳定不变）
	
	for(i=0;i<8;i++){   			  //一次传8位即为一字节
		if(data & 0x80){			  //数据从最高为开始传输
			GPIO_SetBits(GPIOB, GPIO_Pin_7);//检测到高位传一位高位
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);//检测到地位传一位低位
		}
		GPIO_SetBits(GPIOB, GPIO_Pin_6);//拉高时钟位，进行传输
		drv_systick_delay_us(5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟位，当时钟线为低时，数据线上的数据可以发生改变
		//drv_systick_delay_us(5);
		data=data<<1;				  //发送下一位
	}
}
////把时钟线拉高，获取数据线上的数据，接收完数据以后必须要把时钟线拉低，允许从机发送下一个位的数据
u8 drv_iic_readbyte(u8 ack_flag)//ack_flag：发送应答/非应答信号标志
{
	uint8_t read_data=0,i;
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//拉低时钟线使数据线无效，防止误触发
	drv_sda_in();					  //将数据线设置为输入

	for(i=0;i<8;i++){
		read_data=read_data<<1;
		GPIO_SetBits(GPIOB, GPIO_Pin_6);//拉高时钟线，读取有效数据
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)){//当数据线读取到高电平时
			read_data |= 0x01;
		}
		drv_systick_delay_us(5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		drv_systick_delay_us(5);
	}
	if(ack_flag == ACK){
		drv_iic_sendACK();
	}else{
		drv_iic_sendNOACK();
	}
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	return read_data;
}

