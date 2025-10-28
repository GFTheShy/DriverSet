#ifndef _DRV_AT24C02_H_
#define _DRV_AT24C02_H_
#include "stm32f4xx.h"
uint8_t drv_at24cxx_write(uint8_t addr,uint8_t data);
uint8_t drv_at24cxx_read(uint8_t addr);


#endif

