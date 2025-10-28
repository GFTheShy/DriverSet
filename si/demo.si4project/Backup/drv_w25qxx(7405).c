#include "drv_w25qxx.h"
/**************************************************
函数名称：drv_w25qxx_readID
函数功能：读取w25qxx的厂商ID和设备ID
输入参数：无
输出参数：w25qxx的厂商ID和设备ID
其它说明：		命令 0x90
***************************************************/
uint16_t drv_w25qxx_readID(void)
{
	uint16_t read_id=0;

	GPIO_ResetBits(GPIOB, GPIO_Pin_2);//拉低片选信号选择从机

	drv_spi1_wdata(0x90);//发送读取厂商ID和设备ID命令
	
	drv_spi1_wdata(0x00);//发送24为地址
	drv_spi1_wdata(0x00);
	drv_spi1_wdata(0x00);

	read_id = drv_spi1_wdata(0xff);//获取厂商id
	read_id = read_id<<8;
	read_id |= drv_spi1_wdata(0xff);//获取设备id
	GPIO_SetBits(GPIOB, GPIO_Pin_2);//拉高片选取消从机选择
	return read_id;

}

