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
	//drv_systick_delay_ms(30);//消抖
	if(EXTI_GetITStatus(EXTI_Line4))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		TIM_Cmd(TIM5, ENABLE);
		//while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == RESET);
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
extern u8 currentpage;

void EXTI9_5_IRQHandler(void)
{
	//drv_systick_delay_ms(30);
	if(EXTI_GetITStatus(EXTI_Line5))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		TIM_Cmd(TIM5, ENABLE);
		//while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == RESET);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == RESET)//消抖
		{
			
			times2++;

		}
	}

	if(EXTI_GetITStatus(EXTI_Line6))
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		TIM_Cmd(TIM5, ENABLE);
		//while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == RESET);
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == RESET)//消抖
		{
		
		times3++;
		};
		
	}
}
void EXTI15_10_IRQHandler(void)
{
	//drv_systick_delay_ms(30);
	if(EXTI_GetITStatus(EXTI_Line13))//判断外部中断线
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		TIM_Cmd(TIM5, ENABLE);
		//while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == RESET);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == RESET)//消抖
		{
		
		times4++;
		}
	}
}
#include "AD.h"
#include "DHT11.h"
u8 currentflag=0;
u8 temp_val,humi_val;
#include "WIFI.h"
#include "string.h"
extern u8 get;
void TIM6_DAC_IRQHandler (void)//中断函数名要和NVIC通道对应起来，一个字都不能改！
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)){
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		if(times2==1)//切换
		{
			if(currentflag==1){
				if(LED1==0){GPIO_ToggleBits(GPIOE, GPIO_Pin_8);LED1=1;showpage2();OLED_DrawCircle(64, 24, 5);OLED_Refresh();times2=0;return;}
				if(LED1==1){GPIO_ToggleBits(GPIOE, GPIO_Pin_8);LED1=0;showpage2();OLED_DrawCircle(64, 24, 5);OLED_Refresh();times2=0;return;}
			}
			if(currentflag==2){
				if(LED2==0){TIM_SetCompare1(TIM1,300);LED2=1;showpage2();OLED_DrawCircle(64, 40, 5);OLED_Refresh();times2=0;return;}
				if(LED2==1){TIM_SetCompare1(TIM1,50);LED2=2;showpage2();OLED_DrawCircle(64, 40, 5);OLED_Refresh();times2=0;return;}
				if(LED2==2){TIM_SetCompare1(TIM1,0);LED2=0;showpage2();OLED_DrawCircle(64, 40, 5);OLED_Refresh();times2=0;return;}
			}
			if(currentflag==3){
				if(BEEP==0){TIM_SetCompare3(TIM2,100);BEEP=1;showpage2();OLED_DrawCircle(64, 56, 5);OLED_Refresh();times2=0;return;}
				if(BEEP==1){TIM_SetCompare3(TIM2,0);BEEP=2;showpage2();OLED_DrawCircle(64, 56, 5);OLED_Refresh();times2=0;return;}
				if(BEEP==2){TIM_SetCompare3(TIM2,200);BEEP=0;showpage2();OLED_DrawCircle(64, 56, 5);OLED_Refresh();times2=0;return;}
			}
		}
		if(times1==1)//下一个
		{
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
			if(currentpage==2){showpage1();times3=0;return;}
			if(currentpage==3){showpage2();times3=0;return;}
			times3=0;
		}
		else if(times4==1)//下一页
		{
			if(currentpage==1){showpage2();times4=0;return;}
			if(currentpage==2){showpage3();times4=0;return;}
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
	if(currentpage==2){
		OLED_ShowNum(72,32,Get_Adc_Average(),4,16,1);
		if(Get_Adc_Average()<=1000){OLED_ShowChinese(95,48,11,16,1);TIM_SetCompare1(TIM1,0);LED2=0;}//强
		else if(Get_Adc_Average()>1000&&Get_Adc_Average()<2000){OLED_ShowChinese(40,32,12,16,1);OLED_ShowChinese(95,48,12,16,1);TIM_SetCompare1(TIM1,50);LED2=2;}//弱
		else {OLED_ShowChinese(40,32,11,16,1);TIM_SetCompare1(TIM1,200);LED2=1;}
		OLED_Refresh();
		TIM_SetCompare3(TIM2,300);//关闭喇叭
	}
	if(Get_Adc_Average()<=1000){TIM_SetCompare1(TIM1,0);LED2=0;}//强
	else if(Get_Adc_Average()>1000&&Get_Adc_Average()<2000){TIM_SetCompare1(TIM1,50);LED2=2;}//弱
	else {TIM_SetCompare1(TIM1,200);LED2=1;}
	if(currentpage==3){
		DHT11_read_data(&humi_val, &temp_val);
		OLED_ShowNum(50,16,temp_val,2,16,1);
		OLED_ShowNum(50,32,humi_val,2,16,1);
		if(temp_val>=30)TIM_SetCompare2(TIM12,1000);
		else TIM_SetCompare2(TIM12,0);
		OLED_Refresh();
		if(humi_val>=60)TIM_SetCompare3(TIM2,100);
		else TIM_SetCompare3(TIM2,300);	
	}
	if(get==0){
		OLED_ShowString(0, 16,"ready", 16, 1);
		OLED_Refresh();
		}
	
}
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {  
		// 清除中断标志  
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);	
	 	if(get==1){
		OLED_ShowString(0, 16,GET_BUF, 16, 1);
		OLED_Refresh();
		if(strcmp((const char*)GET_BUF,"openled")==0){GPIO_ToggleBits(GPIOE, GPIO_Pin_8);}
		if(strcmp((const char*)GET_BUF,"beep")==0){TIM_SetCompare3(TIM2,200);}
		if(strcmp((const char*)GET_BUF,"beepc")==0){TIM_SetCompare3(TIM2,200);}
		if(strcmp((const char*)GET_BUF,"feng")==0){TIM_SetCompare2(TIM12,1000);}
		memset((char*)GET_BUF,0,sizeof(GET_BUF));
		}
		// 停止定时器  
		TIM_Cmd(TIM5, DISABLE); 
	}
		
}

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
