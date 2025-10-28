#include "WIFI.h"
#include "oled.h"
#include "drv_systick.h"
#include "string.h"
#include "stdio.h"
u8 USART2_RX_BUF[USART2_REC_LEN];//接收缓存，最大USART_REC_LEN个字节
u8 GET_BUF[USART2_REC_LEN];

/*接收状态
bit15，//接收完成标志
bit14，//接收到0x0d
bit13~0，//接收到的有效字节数目*/
u16 USART2_RX_STA=0;//接收状态标记


void WIFI_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//串口2时钟使能

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	//引脚映射
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate=115200;//波特率设置
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长为8位数据格式
	USART_Init(USART2,&USART_InitStructure);
	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_Cmd(USART2, ENABLE);//使能串口

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//串口接收信号时，非空中断

	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//子优先级1
	NVIC_Init(&NVIC_InitStructure);
}
int fputc(int ch,FILE *fp)
{
	USART_SendData(USART2,ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==0);
	USART_ClearFlag(USART2,USART_FLAG_TC);
	return ch;
}

void usart_sendstr(USART_TypeDef * USARTx,char *str,int size)
{
	u8 i=0;
	USART_ClearFlag(USARTx, USART_FLAG_TC);
	for(i=0;i<size;i++){
		USART_SendData(USARTx,*str);
		while(RESET==USART_GetFlagStatus(USARTx, USART_FLAG_TC));
		USART_ClearFlag(USARTx, USART_FLAG_TC);
		str++;
	}
}
u8 can=0;
#include "string.h"
extern u8 get=0;
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)){
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		res=USART_ReceiveData(USART2);
		USART_SendData(USART1, res);
		if((USART2_RX_STA&0x8000)==0)//接收未完成，&0x8000是为了判断最高位是否为1
		{
			if(USART2_RX_STA&0x4000)//判断是否接收到了0x0d,接收到了0x0d那么最高位的下一位会变为1
			{
				
				if(res!=0x0a)USART2_RX_STA=0;//接收错误，重新开始
				else {
					USART2_RX_STA|= 0x8000;//接收完成，给最高位置1
					get=1;
					strcpy((char*)GET_BUF,(char*)USART2_RX_BUF);
					if(strcmp((const char*)USART2_RX_BUF,"CONNECT"))can=1;
				}
			}
			else
			{
				if(res==0x0d){USART2_RX_STA|= 0x4000;}		
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0x3FFF]=res;//&0x3FFF将最高两位清零
					USART2_RX_STA++;
				 	if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据长度不能大于USART_REC_LEN-1
				}
			}
		}	
	}
	
}
void WIFI_connect(void)
{
	u8 i=0;
	usart_sendstr(USART2, "AT+RESTORE\r\n",sizeof("AT+RESTORE\r\n"));
	drv_systick_delay_ms(500);

	usart_sendstr(USART2, "AT\r\n",sizeof("AT+RESTORE\r\n"));
	drv_systick_delay_ms(500);
	
	usart_sendstr(USART2,"AT+CWMODE=1\r\n",sizeof("AT+CWMODE=1\r\n"));
	for(i=0;i<10;i++){drv_systick_delay_ms(100);}
	
	//if(can==1){OLED_ShowString(0,0, USART_RX_BUF, 16, 1);OLED_Refresh();can=0;USART_RX_STA=0;}
	//else {OLED_ShowString(0,0,"error:AT+CWMODE=1", 16, 1);OLED_Refresh();}

	usart_sendstr(USART2,"AT+CWJAP_CUR=\"DESKTOP-CJGM9VL 6508\",\"12345678\"\r\n",sizeof("AT+CWJAP_CUR=\"DESKTOP-CJGM9VL 6508\",\"12345678\"\r\n"));
	for(i=0;i<7;i++){drv_systick_delay_ms(1000);}
	//if(can==1){OLED_ShowString(0,0, USART_RX_BUF, 16, 1);OLED_Refresh();can=0;USART_RX_STA=0;}
	//else {OLED_ShowString(0,0,"error:AT+CWJAP_CUR", 16, 1);OLED_Refresh();}
	
	usart_sendstr(USART2,"AT+CIPSTART=\"TCP\",\"192.168.137.60\",8080\r\n",sizeof("AT+CIPSTART=\"TCP\",\"192.168.137.227\",8080\r\n"));
	for(i=0;i<5;i++){drv_systick_delay_ms(1000);}
	//if(can==1){OLED_ShowString(0,0, USART_RX_BUF, 16, 1);OLED_Refresh();can=3;}
	//else {OLED_ShowString(0,0,"error:AT+CIPSTART", 16, 1);OLED_Refresh();}

	usart_sendstr(USART2, "AT+CIPSEND=24\r\n",sizeof("AT+CIPSEND=24\r\n"));
	drv_systick_delay_ms(500);
	
	if(can==1){OLED_ShowString(0,0, "Succeed", 16, 1);OLED_ShowString(0,0,GET_BUF, 16, 1);OLED_Refresh();can=0;}
}

