#include "drv_spi.h"

void drv_spi1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//3：SCK1 4:MISO1 5：MOSI1 
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;//CS片选
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);


	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//波特率4分频
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;//后沿采集
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;//空闲为高电平
	SPI_InitStruct.SPI_CRCPolynomial = 7;	//配置CRC（循环冗余校验）
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//数据大小为8位
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//方向为双线全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//高位先行
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//模式为主机模式
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//片选信号（Slave Select）的控制方式为软件控制
	SPI_Init(SPI1, &SPI_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	
	SPI_Cmd(SPI1, ENABLE);
}

uint8_t drv_spi1_wdata(uint8_t data)
{
	uint8_t read_data=0;
	//等待SPI1接口的发送缓冲区为空（TXE - Transmit buffer empty）的标志位被置位。为空置1
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI1, data);//通过SPI1接口发送一个数据字节，将数据写入SPI的发送缓冲区，并启动数据的发送过程。
	// 等待接收缓冲区非空，非空置1
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
	read_data = SPI_I2S_ReceiveData(SPI1);// 读取接收缓冲区的数据

	return read_data;

}



