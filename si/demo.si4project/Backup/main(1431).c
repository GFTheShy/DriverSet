#include"drv_led.h"
#include"drv_bee.h"
#include"drv_key.h"
#include"drv_oled.h"
#include"exit.h"

uint8_t p='0';
uint8_t t=0;



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	OLED_Init();
	EXITX_Init();
	drv_led_init();
	drv_key_init();

	while (1)
	{
		p++;
		t++;
		OLED_ShowChar(t, 1, p);
		delay_ms(500);
	}

}
