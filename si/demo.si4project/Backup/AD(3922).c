#include "AD.h"
uint16_t adc_buf[100];
/**************************************************
函数名称：drv_adc1_init

函数功能：adc1初始化

输入参数：无

输出参数：无
其它说明：
			ADC1的通道0 采集光敏传感器的值
***************************************************/
void drv_adc1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;//模拟功能
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//失能DMA直接访问
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;//168/2/4=21M
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//采样间隔时间延迟5个周期
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize = 100;//需要搬运的数据的数量
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;//通道号
	DMA_InitStruct.DMA_DIR =DMA_DIR_PeripheralToMemory;//外设到内存
	DMA_InitStruct.DMA_FIFOMode =DMA_FIFOMode_Disable;//不使用fifo模式
	DMA_InitStruct.DMA_Memory0BaseAddr =(uint32_t)adc_buf;//目标地址
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次触发
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//数据半字传输
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//目标地址自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//循环缓存模式

	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//数据来源地址
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//优先级高
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);//设置采样规则，采样时间
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);//设置DMA触发条件
	DMA_Cmd(DMA2_Stream0, ENABLE);//使能DMA
	ADC_Cmd(ADC1, ENABLE);//使能adc1
	ADC_DMACmd(ADC1, ENABLE);//使能adc的DMA

	ADC_SoftwareStartConv(ADC1);//软件触发ADC转换
}
/**************************************************
函数名称：drv_adc_value

函数功能：取光敏传感器采集值的平均值

输入参数：无

输出参数：平均值
其它说明：
			ADC1的通道0 采集光敏传感器100次取平均值
***************************************************/
uint16_t drv_adc_value(void)
{
	uint8_t i;
	uint32_t sum;
	for(i=0;i<100;i++)
	{
		sum = sum + adc_buf[i];
	}
	return (uint16_t)(sum/100);
}
