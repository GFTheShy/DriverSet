#ifndef _DRV_IIC_H__
#define _DRV_IIC_H__
#include "stm32f4xx.h"
#define ACK 0
#define NOACK 1
void drv_iic_init(void);
void drv_sda_in(void);
void drv_sda_out(void);
void drv_iic_start(void);
void drv_iic_stop(void);
void drv_iic_sendACK(void);
void drv_iic_sendNOACK(void);
u8 drv_iic_waitACK(void);
void drv_iic_sendbyte(u8 data);
u8 drv_iic_readbyte(u8 ack_flag);


#endif

