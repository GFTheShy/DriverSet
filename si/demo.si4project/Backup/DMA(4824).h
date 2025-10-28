#ifndef _DMA_H_
#define _DMA_H_
#include"stm32f4xx.h"
void My_DMA_Init(DMA_Stream_TypeDef * DMA_Streamx,u32 chx,u32 AddrA,u32 AddrB,u16 Size);
void MY_DMA_Enable(DMA_Stream_TypeDef * DMA_Streamx,u16 Size);

#endif
