#include "stdio.h"
#include "oled.h"
#include "bmp.h"
#include "drv_systick.h"
#include "AD.h"
#include "usart.h"

uint32_t buf[10]={0x11111111,0x22222222,0x33333333,0x44444444,0x22222222,
				  0x11111111,0x22222222,0x33333333,0x44444444,0x22222222};
uint32_t dma_buf[10]={0};

#define SEND_BUF_SIZE 82

u8 SendBuf[SEND_BUF_SIZE];
const u8 TEST_TO_SEND[]={"88888888888888888888"};

u16 ledOpwM=0,t;
u8 dir=0;
void delay_ms(uint32_t ms)
{
	uint32_t i;
    // 基于系统时钟的粗略延时函数
    for ( i = 0; i < (ms * 10000); ++i) {
        __NOP();
    }
}

int main(void)
{

	My_USART1_Init();

	drv_systick_init(168);

	OLED_Init();

	OLED_ShowChinese(0,16,0,16,1);//华
	OLED_ShowChinese(20,16,1,16,1);//清
	OLED_ShowChinese(40,16,2,16,1);//远
	OLED_ShowChinese(60,16,3,16,1);//见
	OLED_ShowChinese(80,16,4,16,1);//教
	OLED_ShowChinese(100,16,5,16,1);//育
	OLED_ShowChinese(120,16,5,16,1);//欢
	OLED_ShowChinese(140,16,5,16,1);//迎
	OLED_ShowChinese(160,16,5,16,1);//您
	//OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
	//OLED_ShowString(20,32,"2014/05/01",16,1);
	OLED_Refresh();
	OLED_ScrollDisplay(10,4,1);
	while(1)
	{

		/*//OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);//华
		OLED_ShowChinese(18,0,1,16,1);//清
		OLED_ShowChinese(36,0,2,16,1);//远
		OLED_ShowChinese(54,0,3,16,1);//见
		OLED_ShowChinese(72,0,4,16,1);//教
		OLED_ShowChinese(90,0,5,16,1);//育
		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		OLED_ShowString(20,32,"2014/05/01",16,1);
		OLED_ShowString(0,48,"ASCII:",16,1);  
		OLED_ShowString(63,48,"CODE:",16,1);
		OLED_ShowChar(48,48,t,16,1);//ÏÔÊ¾ASCII×Ö·û	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16,1);
		OLED_Refresh();
		//delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);  //16*16 ÖÐ
	  OLED_ShowChinese(16,0,0,24,1); //24*24 ÖÐ
		OLED_ShowChinese(24,20,0,32,1);//32*32 ÖÐ
	  OLED_ShowChinese(64,0,0,64,1); //64*64 ÖÐ
		OLED_Refresh();
	  delay_ms(500);
  	OLED_Clear();
		OLED_ShowString(0,0,"ABC",8,1);//6*8 ¡°ABC¡±
		OLED_ShowString(0,8,"ABC",12,1);//6*12 ¡°ABC¡±
	  OLED_ShowString(0,20,"ABC",16,1);//8*16 ¡°ABC¡±
		OLED_ShowString(0,36,"ABC",24,1);//12*24 ¡°ABC¡±
	  OLED_Refresh();
		delay_ms(500);
		OLED_ScrollDisplay(11,4,1);*/
	}		
	
}

