#ifndef _DRV_LED_H__
#define	_DRV_LED_H__
#include"stm32f4xx.h"

void drv_led_init(void);
void drv_led_open(uint16_t GPIO_Pin);
void drv_led_close(uint16_t GPIO_Pin);
void drv_led_closeall(void);


#endif

