#include"drv_led.h"
#include"drv_bee.h"
#include"drv_key.h"

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
	drv_led_init();//初始化
	drv_key_init();
	drv_bee_init();
	while(1)
	{
		uint8_t p=keyout();
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
