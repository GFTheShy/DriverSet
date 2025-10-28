#include "DHT11.h"
#include "drv_systick.h"
void DHT11_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	DHT11_output();//完全重复的代码可以直接调用

}
void DHT11_input(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void DHT11_output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_SetBits(GPIOA, GPIO_Pin_3);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
//从DHT11读取数据位，每次读取8个位，并返回
u8 DHT11_read_bitdata(void)
{
	u8 i;
	u8 dat;
	for(i=0;i<8;i++)
	{
		dat<<=1;
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));//等待引脚为低电平

		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)==0);//等待引脚由低变为高电平

		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))//测量高电平的时间
		{
			drv_systick_delay_us(30);
		}
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))dat |= 1;//30us后还是高电平，说明DHT11传递的数据就是数据位1
		
	}
	return dat;
}	
/*
	通过参数将温度和湿度返回
	返回值：
			0：成功读取到温度和湿度
			其他值：表示读取失败
*/
u8 DHT11_read_data(u8 * humi,u8 * temp)
{	
	u8 retry=0,i,buf[5];
	//1.由单片机发送起始信号
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	drv_systick_delay_ms(20);//必须拉低20ms
	//转为高电平
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	drv_systick_delay_us(30);//再拉高30us
	//引脚调为输入模式，等待DHT11的响应
	DHT11_input();
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))//等待引脚为低电平
	{
		retry++;
		drv_systick_delay_us(5);
		if(retry>10)
		{
			printf("%s %d\n",__FUNCTION__,__LINE__);
			return 1;//出错	
		}
	}
	retry=0;
	//等待引脚由低变为高电平
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)==0){
		retry++;
		drv_systick_delay_us(10);
		if(retry>10)
		{
			printf("%s %d\n",__FUNCTION__,__LINE__);
			return 1;//出错	
		}
	}
	//读取数据
	for(i=0;i<5;i++)
	{
		buf[i]=DHT11_read_bitdata();
	}
	//引脚为输出模式
	DHT11_output();
	
	if(buf[0]+buf[1]+buf[2]+buf[3]==buf[4])//校验成功
	{
		*humi = buf[0];
		*temp = buf[2]; 
		return 0;//成功
	}
	printf("%s %d\n",__FUNCTION__,__LINE__);
	return 1;//错误
}

