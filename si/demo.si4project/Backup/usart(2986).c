#include"usart.h"

u8 state=0;
u8 n=0;
#include "string.h"
#include "usart.h"
u8 USART_RX_BUF[USART_REC_LEN];//接收缓存，最大USART_REC_LEN个字节
/*接收状态
bit15，//接收完成标志
bit14，//接收到0x0d
bit13~0，//接收到的有效字节数目*/
u16 USART_RX_STA=0;//接收状态标记



void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//串口1时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

	//引脚映射
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);//GPIOA10复用为USART1

 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=115200;//波特率设置
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长为8位数据格式
	USART_Init(USART1,&USART_InitStructure);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1, ENABLE);//使能串口
	

	

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//串口接收信号时，非空中断

	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//子优先级1
	NVIC_Init(&NVIC_InitStructure);
	

}

int fputc(int ch,FILE *fp)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	return ch;
}
void USART1_IRQHandler(void)//中断处理函数
{
	u16 RES;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET){
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		RES=USART_ReceiveData(USART1);
		if(RES=='o'&&state==0){
			GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
			state=1;
		}if(RES=='c'&&state==1){
			GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
			state=0;
		}
	}
	/*u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
		res=USART_ReceiveData(USART1);
		if((USART_RX_STA&0x8000)==0)//接收未完成，&0x8000是为了判断最高位是否为1
		{
			if(USART_RX_STA&0x4000)//判断是否接收到了0x0d,接收到了0x0d那么最高位的下一位会变为1
			{
				if(res!=0x0a)USART_RX_STA=0;//接收错误，重新开始
				else USART_RX_STA|= 0x8000;//接收完成，给最高位置1
			}
			else
			{
				if(res==0x0d)USART_RX_STA|= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0x3FFF]=res;//&0x3FFF将最高两位清零
					USART_RX_STA++;
				if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据长度不能大于USART_REC_LEN-1
				}
			}
		}
			
	}*/

}
