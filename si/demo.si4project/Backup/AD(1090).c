#include "AD.h"
#include "drv_systick.h"

void AD_init(void)
{
	ADC_InitTypeDef  ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	ADC_DeInit();


	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);

	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_144Cycles);
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;//选择软件触发
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//单次转换
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//非扫描
	ADC_InitStruct.ADC_NbrOfConversion=1;//只转换规则序列1
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);

}
u16 Get_Adc(u8 ch)//获得某个通道值
{
	
	ADC_SoftwareStartConv(ADC1);//软件开启转换

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);//等待转换结束

	return ADC_GetConversionValue(ADC1);//获取转换结果
}
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val += Get_Adc(ch);
		drv_systick_delay_ms(500);
	}
	return temp_val/times;
}
