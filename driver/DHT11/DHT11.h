#ifndef _DHT11_H__
#define _DHT11_H__
#include "stm32f4xx.h"
void DHT11_init(void);
void DHT11_input(void);
void DHT11_output(void);
//从DHT11读取数据位，每次读取8个位，并返回
u8 DHT11_read_bitdata(void);
u8 DHT11_read_data(u8 * humi,u8 * temp);


#endif
