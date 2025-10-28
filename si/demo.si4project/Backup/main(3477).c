#include "drv_led.h"
#include "drv_bee.h"
#include "drv_key.h"
#include "drv_oled.h"
#include "exit.h"
#include "drv_systick.h"
#include "drv_key2.h"
#include "drv_iwdog.h"
#include "usart.h"



int main(void)
{
	u8 len,t;
	//u16 times=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	drv_led_init();
	drv_bee_init();
	
	/*drv_led_init();
	drv_systick_init(168);
	drv_key2_init();
	


	drv_systick_delay_ms(500);

	drv_bee_open();

	
		drv_iwdog_init(4,1000);

	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==RESET){
			IWDG_ReloadCounter();
		}
		drv_systick_delay_ms(20);
	}*/

	My_USART1_Init();
	printf("hhhhhhhhhh\r\n");

	while(1)
	{
		if(USART_RX_STA&0x8000)
		{	
			GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
			len=USART_RX_STA&0x3fff;
			printf("ddddddddddd:\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}
			printf("\r\n\r\n");
			USART_RX_STA=0;
		}/*else
			{
				times++;
				if(times%5000==0)
					{
						printf("\r\nAAAAAAA\r\n");
						printf("BBBBBBB\r\n");
					}
				if(times%200==0)printf("CCCCCCCCCCCC\r\n");
				if(times%30==0)GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
				drv_systick_delay_ms(20);
			}*/
		

	}
	
}

