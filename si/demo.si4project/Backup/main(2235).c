#include "drv_led.h"
#include "drv_bee.h"
#include "drv_key.h"
#include "drv_oled.h"
#include "exit.h"
#include "drv_systick.h"
#include "drv_key2.h"
#include "drv_iwdog.h"

uint8_t p='0';
uint8_t t=0;
void My_USART1_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//串口1时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

	//引脚映射
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);//GPIOA10复用为USART1

 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=115200;//波特率设置
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长为8位数据格式
	USART_Init(USART1,&USART_InitStructure);

	USART_Cmd(USART1, ENABLE);//使能串口

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//串口接收信号时，非空中断

	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//子优先级1
	NVIC_Init(&NVIC_InitStructure);
}
void USART1_IRQHandler(void)//中断处理函数
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1, res);
	}
}


int main(void)
{
	/*NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init();
	while(1);*/
	drv_led_init();
	drv_systick_init(168);
	drv_key2_init();
	drv_bee_init();

	/*while (1)
	{
		//key_event();
		drv_led_open(8);
		drv_systick_delay_ms(1000);
		drv_led_close(8);
		drv_systick_delay_ms(1000);
	}*/

	/*drv_bee_open();
	drv_systick_delay_ms(50);
	drv_bee_close();
	drv_systick_delay_ms(50);
	drv_bee_open();
	drv_systick_delay_ms(50);
	drv_bee_close();
	drv_systick_delay_ms(50);
	drv_bee_open();
	drv_systick_delay_ms(50);
	drv_bee_close();
	drv_systick_delay_ms(500);*/
	drv_led_open(8);
	drv_systick_delay_ms(50);
		drv_iwdog_init(4,1000);

	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)){
			IWDG_ReloadCounter();
		}
	}
	
}

