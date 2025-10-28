#include "drv_systick.h"
static u8 fs_us;
static u16 fs_ms;
void drv_systick_init(u8 systick)
{
	SysTick->CTRL &= (~0x05);
	fs_us= systick/8;
	fs_ms= fs_us*1000;
}
void drv_systick_delay_us(u32 us)
{
	u32 temp=0;
	SysTick->LOAD=fs_us*us;
	SysTick->VAL=0;
	SysTick->CTRL |= 0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while (!(temp &= (0x01<<16)));
	SysTick->CTRL &= ~0x01;
	
}

void drv_systick_delay_ms(u32 ms)
{
	u32 temp=0;
	u8 n=fs_ms*ms/16777215;
	u32 buf=fs_ms*ms%16777215;
	SysTick->CTRL |= 0x01;
	while(n)
	{
		SysTick->LOAD=fs_ms*ms;
		SysTick->VAL=0;
		
		do
		{
			temp=SysTick->CTRL;
		}
		while (!(temp &= (0x01<<16)));
		
		n--;
	}
	SysTick->LOAD=buf;
	SysTick->VAL=0;	
	do
	{
		temp=SysTick->CTRL;
	}
	while (!(temp &= (0x01<<16)));
	SysTick->CTRL &= ~0x01;
	
}

