#include "drv_iwdog.h"

void drv_iwdog_init(u8 prer,u16 Reload)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(prer);
	IWDG_SetReload(Reload);
	IWDG_ReloadCounter();
	IWDG_Enable();
}
