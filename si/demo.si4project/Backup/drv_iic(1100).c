#include "drv_iic.h"
#include "drv_systick.h"
/**************************************************
函数名称：drv_iic_init
函数功能：IIC初始化函数
输入参数：无
输出参数：无
其它说明：//pb6 - scl
		  //pb7 - sda
***************************************************/
void drv_iic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//开时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//gpio参数配置
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
/**************************************************
函数名称：drv_sda_in
函数功能：将sda数据线设置为输入
输入参数：无
输出参数：无
其它说明：//pb6 - scl
		  //pb7 - sda
***************************************************/
void drv_sda_in(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
/**************************************************
函数名称：drv_sda_out
函数功能：将sda数据线设置为输出
输入参数：无
输出参数：无
其它说明：//pb6 - scl
		  //pb7 - sda
***************************************************/
void drv_sda_out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
/**************************************************
函数名称：drv_iic_start
函数功能：模拟IIC起始信号
输入参数：无
输出参数：无
其它说明：当时钟线为高电平时，数据线由高电平变为低电平，产生一个有效的下降沿
***************************************************/
void drv_iic_start(void)
{
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_out();			//将数据线设置为输出

	SDA_H;					//拉高数据线
	SCL_H;					//拉高时钟线使数据有效
	drv_systick_delay_us(5);	//时序要求大于4.7US
	SDA_L;					//拉低数据线，产生下降沿
	drv_systick_delay_us(5);	//时序要求大于4US
	SCL_L;					//拉低时钟线占用IIC总线
}
/**************************************************
函数名称：drv_iic_stop
函数功能：模拟IIC停止信号
输入参数：无
输出参数：无
其它说明：当时钟线为高电平时，数据线由低电平变为高电平，产生一个有效的上升沿
***************************************************/
void drv_iic_stop(void)
{
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_out();			//将数据线设置为输出

	SDA_L;					//拉低数据线
	SCL_H;					//拉高时钟线使数据有效
	drv_systick_delay_us(5);	//时序要求大于4US
	SDA_H;					//拉高数据线，产生上升沿
	drv_systick_delay_us(5);	//时序要求大于4.7US
}
/**************************************************
函数名称：drv_iic_sendACK
函数功能：模拟IIC发送应答信号
输入参数：无
输出参数：无
其它说明：当时钟线为高电平时，数据线产生一个有效的低电平
***************************************************/
void drv_iic_sendACK(void)
{
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_out();			//将数据线设置为输出

	SDA_L;					//拉低数据线
	SCL_H;					//拉高时钟，使数据有效
	drv_systick_delay_us(5);	//时序要求大于4US
	SCL_L;					//拉低时钟线占用IIC总线
}
/**************************************************
函数名称：drv_iic_sendNOACK
函数功能：模拟IIC发送非应答信号
输入参数：无
输出参数：无
其它说明：当时钟线为高电平时，数据线产生一个有效的高电平
***************************************************/
void drv_iic_sendNOACK(void)
{
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_out();			//将数据线设置为输出

	SDA_H;					//拉低数据线
	SCL_H;					//拉高时钟，使数据有效
	drv_systick_delay_us(5);	//时序要求大于4US
	SCL_L;					//拉低时钟线占用IIC总线
}
/**************************************************
函数名称：drv_iic_waitACK
函数功能：模拟IIC等待应答信号
输入参数：无
输出参数：根据读取的结果返回ACK或者NOACK
其它说明：把时钟线拉高，读取数据线上的数据：高电平（非应答）、低电平（应答）
***************************************************/
uint8_t drv_iic_waitACK(void)
{
	uint16_t time_out=0;
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_in();			//将数据线设置为输入

	SCL_H;					//拉高数据线
	while(SDA_READ)			//读取数据
	{
		time_out++;
		if(time_out > 300) //超时没有等到应答信号返回NOACK
		{
			drv_iic_stop();
			return NOACK;
		}
	}
	return ACK;
}
/**************************************************
函数名称：drv_iic_sendbyte

函数功能：模拟IIC发送一个字节数据

输入参数：data：需要发送的数据

输出参数：无

其它说明：把时钟线拉高，读取数据线上的数据：高电平（非应答）、低电平（应答）
***************************************************/
void drv_iic_sendbyte(uint8_t data)
{
	uint8_t i=0;
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_out();			//将数据线设置为输出

	for(i=0;i<8;i++)       //循环8次，总共发送一个字节出去
	{
		if(data & 0x80)
		{
			SDA_H;	
		}
		else
		{
			SDA_L;
		}
		SCL_H;
		drv_systick_delay_us(5);
		SCL_L;
		drv_systick_delay_us(5);
		data = data << 1;	//发送下一个位
	}
}
/**************************************************
函数名称：drv_iic_readbyte

函数功能：模拟IIC读取一个字节数据

输入参数：ack_flag：发送应答/非应答信号标志

输出参数：read_data：读取的数据

其它说明：把时钟线拉高，获取数据线上的数据，接收完数据以后必须要把时钟线拉低，允许从机发送下一个位的数据
***************************************************/
uint8_t drv_iic_readbyte(uint8_t ack_flag)
{
	uint8_t read_data=0,i;
	SCL_L;					//拉低时钟线使数据无效，防止误触发
	drv_sda_in();			//将数据线设置为输入

	for(i=0; i<8; i++)
	{
		read_data = read_data<<1;
		SCL_H;
		if(SDA_READ)
		{
			read_data = read_data|0x01;
		}
	drv_systick_delay_us(5);
		SCL_L;
		drv_systick_delay_us(5);
	}
	if(ack_flag == ACK)
	{
		drv_iic_sendACK();
	}
	else
	{
		drv_iic_sendNOACK();
	}
	SCL_L;
	return read_data;
}
