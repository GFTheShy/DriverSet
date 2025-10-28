#include "drv_systick.h"
static u8 fs_us;
static u16 fs_ms;
void drv_systick_init(u8 systick)
{
	SysTick->CTRL &= (~0x05);
	fs_us= systick/8;
	fs_ms= fs_us*1000;
}

void drv_systick_delay(u16 ms)
{
	u32 temp=0;
	SysTick->LOAD=fs_ms*ms;
	SysTick->VAL=0;
	SysTick->CTRL |= 0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while (!(temp &= (0x01<<16)));
	SysTick->CTRL &= ~0x01;
	
}

