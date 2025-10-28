#include"drv_led.h"
#include"drv_bee.h"
#include"drv_key.h"


uint8_t p;



int main(void)
{
	drv_led_init();//初始化
	drv_key_init();
	drv_bee_init();
	while(1)
	{
		p=key_GETNUM();
		if(p==1)
			{
				drv_led_open(8);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(500);
				
			}
		if(p==2)
			{
				drv_led_open(9);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(100);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(500);
			}
		if(p==3)
			{
				drv_led_open(10);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(100);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(100);
				drv_bee_open();
				delay_ms(100);
				drv_bee_close();
				delay_ms(500);
			}
	}
}
