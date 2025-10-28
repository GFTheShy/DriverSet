/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
#include "drv_key.h"
#include "drv_systick.h"
#include "drv_led.h"
#include "timer.h"
u8 times1=0;
u8 times2=0;
u8 times3=0;
u8 times4=0;

void EXTI4_IRQHandler(void)
{
	drv_systick_delay_ms(30);//消抖
	if(EXTI_GetITStatus(EXTI_Line4))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == RESET)//消抖
		{
			
			times1++;
		}
	}
}
#include "oled.h"
#include "pwm.h"
u8 LED1=0;
u8 LED2=0,LEDSTATE=0;
u8 BEEP=0;
u8 currentpage=0;

void EXTI9_5_IRQHandler(void)
{
	drv_systick_delay_ms(30);
	if(EXTI_GetITStatus(EXTI_Line5))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == RESET)//消抖
		{
			
			times2++;

		}
	}

	if(EXTI_GetITStatus(EXTI_Line6))
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == RESET)//消抖
		{
			
			times3++;
		};
		
	}
}
void EXTI15_10_IRQHandler(void)
{
	drv_systick_delay_ms(30);
	if(EXTI_GetITStatus(EXTI_Line13))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == RESET)//消抖
		{
			
			times4++;
		}
	}
}
u8 currentflag=0;
void TIM6_DAC_IRQHandler(void)//中断函数名要和NVIC通道对应起来，一个字都不能改！
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)){
		if(times2==1)//切换
		{
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
			//if(times==1)GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
			GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
			LED1 = !LED1;
			times2=0;
		}
		if(times1==1)//下一个
		{
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
			if(currentflag==0 || currentflag==3){
				currentflag=1;
				OLED_Clear();
				showpage2();
				OLED_DrawCircle(64, 24, 5);
				OLED_Refresh();
				times1=0;
				return;
			}
			if(currentflag==1){
				currentflag=2;
				OLED_Clear();
				showpage2();
				OLED_DrawCircle(64, 40, 5);
				OLED_Refresh();
				times1=0;
				return;
			}
			if(currentflag==2){
				currentflag=3;
				OLED_Clear();
				showpage2();
				OLED_DrawCircle(64, 56, 5);
				OLED_Refresh();
				times1=0;
				return;
			}
			//TIM_SetCompare1(TIM1,10);
			//LED2 = !LED2;
			
		}

		if(times3==1)//上一页
		{
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
			if(currentpage==2)showpage1();
			times3=0;
		}
		if(times4==1)//下一页
		{
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
			if(currentpage==1)showpage2();
			times4=0;
		}
		else 
		{
			times1=0;
			times2=0;
			times3=0;
			times4=0;
		}
	}
	
}



/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
