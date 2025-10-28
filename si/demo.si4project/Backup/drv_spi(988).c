#include "drv_spi.h"


/**************************************************
º¯ÊýÃû³Æ£ºdrv_spi_init
º¯Êý¹¦ÄÜ£ºSPI1³õÊ¼»¯º¯Êý
ÊäÈë²ÎÊý£ºÎÞ
Êä³ö²ÎÊý£ºÎÞ
ÆäËüËµÃ÷£º		//cs - pb2
			//clk - pb3 
			//miso - pb4
			//mosi - pb5 
			//loracs - pe1
***************************************************/
void drv_spi1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//W25QxxÆ¬Ñ¡
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//loraÄ£¿éÆ¬Ñ¡
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);//Ö¸¶¨ioµÄ¸´ÓÃ¹¦ÄÜ
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);


	//spi²ÎÊý³õÊ¼»¯£¬¸ù¾ÝÇý¶¯Éè±¸µÄÊÖ²á½øÐÐ³õÊ¼»¯£¨W25Q64Êý¾ÝÊÖ²á£©
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//Ê±ÖÓ·ÖÆµ
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;//Ê±ÖÓÏàÎ»£¬ºóÑØ²ÉÑù
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;//Ê±ÖÓ¼«ÐÔ£¬Ê±ÖÓ¿ÕÏÐÊ±Îª¸ß
	SPI_InitStruct.SPI_CRCPolynomial = 7;//crcÐ£Ñé
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//8Î»Êý¾ÝÎ»
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//Á½ÏßÈ«Ë«¹¤
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//¸ßÎ»ÏÈÐÐ
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//Ö÷»úÄ£Ê½
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//Èí¼þ¿ØÖÆ
	SPI_Init(SPI1, &SPI_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	
	SPI_Cmd(SPI1, ENABLE);
}
/**************************************************
º¯ÊýÃû³Æ£ºdrv_spi1_readata
º¯Êý¹¦ÄÜ£ºSPI1¶ÁÈ¡Êý¾Ý
ÊäÈë²ÎÊý£ºÎÞ
Êä³ö²ÎÊý£ºÎÞ
ÆäËüËµÃ÷£º		¶ÁÈ¡Ö®Ç°ÏÈ·¢ËÍ
***************************************************/
uint8_t drv_spi1_wdata(uint8_t data)
{
	uint8_t read_data=0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI1, data);
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
	read_data = SPI_I2S_ReceiveData(SPI1);

	return read_data;

}



