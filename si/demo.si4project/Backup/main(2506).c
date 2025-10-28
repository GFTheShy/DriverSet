#include"drv_led.h"
#include"drv_bee.h"
#include"drv_key.h"
#include"drv_oled.h"

uint8_t p;



int main(void)
{
	OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	
}
