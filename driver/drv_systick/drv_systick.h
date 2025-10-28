#ifndef _DRV_SYSTICK_H__
#define _DRV_SYSTICK_H__
#include "stm32f4xx.h"

void drv_systick_init(u8 systick);
void drv_systick_delay_us(u32 us);
void drv_systick_delay_ms(u32 ms);


#endif
