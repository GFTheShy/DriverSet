#include"drv_led.h"
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
	while(1)
	{
		drv_led_open(8);
		delay_ms(100);
		drv_led_close(8);
		delay_ms(100);
		drv_led_open(9);
		delay_ms(100);
		drv_led_close(9);
		delay_ms(100);
		drv_led_open(10);
		delay_ms(100);
		drv_led_close(10);
		delay_ms(100);
	}
}
