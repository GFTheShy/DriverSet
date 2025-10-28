#ifndef _DRV_LED_H__
#define	_DRV_LED_H__
#include"stm32f4xx.h"

void drv_led_init(void);
void drv_led_open(int P);
void drv_led_close(int P);
void drv_led_closeall(void);


#endif

