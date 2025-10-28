#include "DMA.h"

//参数：确定要配置的数据流，通道选择，外设基地址，寄存器基地址，传输的数据量
void My_DMA_Init(DMA_Stream_TypeDef * DMA_Streamx,u32 chx,u32 AddrA,u32 AddrB,u16 Size)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);

	
	//与DMA2的首地址比较,得到当前Stream是属于DMA2还是DMA1
	if((u32)DMA_Streamx>(u32)DMA2){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	}else{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
	}
	DMA_DeInit(DMA_Streamx);//恢复通道的寄存器到其默认值
	while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE);//等待DMA可配置

	DMA_InitStruct.DMA_Channel=chx;
	DMA_InitStruct.DMA_PeripheralBaseAddr=AddrA;//外设站点的基地址,0x20000000(SRAM)
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//以字节的方式传输
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;//地址自增
	DMA_InitStruct.DMA_Memory0BaseAddr=AddrB;//存储器基地址参数
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToPeripheral;//寄存器到外设
	DMA_InitStruct.DMA_BufferSize=Size;//数据输出量
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;//正常模式
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;//直接模式（非FIFO模式）
	DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;//阈值为完整容量
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;//存储器突发单次传输
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;//外设突发单次传输

	DMA_Init(DMA_Streamx, &DMA_InitStruct); 
	//DMA_Cmd(DMA_Streamx, ENABLE);//初始化后立即工作
	
}
void MY_DMA_Enable(DMA_Stream_TypeDef * DMA_Streamx,u16 Size)
{
	DMA_Cmd(DMA_Streamx, DISABLE);//关闭DMA输出
	while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE);//等待DMA可配置
	DMA_SetCurrDataCounter(DMA_Streamx, Size);//数据传输量
	DMA_Cmd(DMA_Streamx, ENABLE);
}
