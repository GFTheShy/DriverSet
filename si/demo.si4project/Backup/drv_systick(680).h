#ifndef _DRV_SYSTICK_H__
#define _DRV_SYSTICK_H__
#include "stm32f4xx.h"

void drv_systick_init(u8 systick);
void drv_systick_delay(u16 ms);


#endif
