#include "AD.h"
#include "drv_systick.h"
uint16_t adc_buf[100],adc2_buf[100];

void AD_init(void)
{
	ADC_InitTypeDef  ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2,ENABLE);
	//ADC_DeInit();

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);

	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_144Cycles);
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;//选择软件触发
	//ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//单次转换,装完一次buf不会再转第二次了
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;//连续转换，装完一次后覆盖buf内的上一次数据
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;//非扫描，只使用第一个通道
	ADC_InitStruct.ADC_NbrOfConversion=1;//只转换规则序列1
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize=100;
	DMA_InitStruct.DMA_Channel=DMA_Channel_0;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(u32)adc_buf;
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//循环缓存模式

	DMA_InitStruct.DMA_PeripheralBaseAddr=(u32)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_144Cycles);

	ADC_SoftwareStartConv(ADC1);//软件触发ADC转换
}
u16 Get_Adc(u8 ch)//获得某个通道值
{
	
	ADC_SoftwareStartConv(ADC1);//软件开启转换

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);//等待转换结束

	return ADC_GetConversionValue(ADC1);//获取转换结果
}
u16 Get_Adc_Average(void)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<100;t++)
	{
		temp_val += adc_buf[t];
	}
	return (uint16_t)(temp_val/100);
}
u16 Get_Adc2_Average(void)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<100;t++)
	{
		temp_val += adc2_buf[t];
	}
	return (uint16_t)(temp_val/1000);
}

void ADC2_init(void)//DHT11温度传感器	
{
	ADC_InitTypeDef  ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2,ENABLE);
	//ADC_DeInit();

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);

	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_144Cycles);
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;//选择软件触发
	//ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//单次转换,装完一次buf不会再转第二次了
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;//连续转换，装完一次后覆盖buf内的上一次数据
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;//非扫描，只使用第一个通道
	ADC_InitStruct.ADC_NbrOfConversion=1;//只转换规则序列1
	ADC_Init(ADC2, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize=100;
	DMA_InitStruct.DMA_Channel=DMA_Channel_1;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_Memory0BaseAddr=(u32)adc2_buf;
	DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//循环缓存模式

	DMA_InitStruct.DMA_PeripheralBaseAddr=(u32)&ADC2->DR;
	DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	DMA_Init(DMA2_Stream2, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream2, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
	ADC_DMACmd(ADC2, ENABLE);
	ADC_RegularChannelConfig(ADC2,ADC_Channel_3,1,ADC_SampleTime_144Cycles);

	ADC_SoftwareStartConv(ADC2);//软件触发ADC转换
}


