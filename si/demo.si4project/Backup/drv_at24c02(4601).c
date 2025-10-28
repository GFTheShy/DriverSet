#include "drv_iic.h"
#include "drv_at24c02.h"

/**************************************************
函数名称：drv_at24cxx_write

函数功能：向at24cxx写入一个字节数据

输入参数：addr：写入数据的地址                data:写入的数据

输出参数：成功：0；失败返回NOACK

其它说明：
***************************************************/
uint8_t drv_at24cxx_write(uint8_t addr,uint8_t data)
{
	drv_iic_start();			//发送起始信号
	drv_iic_sendbyte(0xa0);		//发送设备地址

	if(drv_iic_waitACK() != ACK)//等待ACK
	{
		drv_iic_stop();
		return NOACK;
	}

	drv_iic_sendbyte(addr);		//发送写入数据的地址
	if(drv_iic_waitACK() != ACK)
	{
		drv_iic_stop();
		return NOACK;
	}

	drv_iic_sendbyte(data);		//发送写入的数据
	if(drv_iic_waitACK() != ACK)
	{
		drv_iic_stop();
		return NOACK;
	}
	drv_iic_stop();
	return 0;
}

/**************************************************
函数名称：drv_at24cxx_read

函数功能：从at24cxx读出一个字节数据

输入参数：addr：需要读取数据的地址

输出参数：成功返回读取到的数据；失败返回NOACK

其它说明：
***************************************************/
uint8_t drv_at24cxx_read(uint8_t addr)
{
	uint8_t read_data=0;
	drv_iic_start();			//发送起始信号
	drv_iic_sendbyte(0xa0);		//发送设备地址

	if(drv_iic_waitACK() != ACK)//等待ACK
	{
		drv_iic_stop();
		return NOACK;
	}
	
	drv_iic_sendbyte(addr); 	//发送读取数据的地址
	
	if(drv_iic_waitACK() != ACK)//等待ACK
	{
		drv_iic_stop();
		return NOACK;
	}

	drv_iic_start();			//发送起始信号
	drv_iic_sendbyte(0xa1);		//发送设备地址
	
	if(drv_iic_waitACK() != ACK)//等待ACK
	{
		drv_iic_stop();
		return NOACK;
	}
	read_data = drv_iic_readbyte(NOACK);
	drv_iic_stop();
	return read_data;
}


