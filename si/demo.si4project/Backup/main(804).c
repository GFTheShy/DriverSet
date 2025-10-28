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
		drv_led_closeall();
		drv_led_open(GPIO_Pin_8);
		delay_ms(500);
		drv_led_close(GPIO_Pin_8);
		delay_ms(500);
		drv_led_open(GPIO_Pin_9);
		delay_ms(500);
		drv_led_close(GPIO_Pin_9);
		delay_ms(500);
		drv_led_open(GPIO_Pin_10);
		delay_ms(500);
		drv_led_close(GPIO_Pin_10);
		delay_ms(500);
	}
}
