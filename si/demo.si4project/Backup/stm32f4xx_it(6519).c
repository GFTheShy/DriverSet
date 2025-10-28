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
u8 state=0;
u8 n=0;
#include "string.h"
char USART_RX_BUF[50];//接收缓存，最大USART_REC_LEN个字节
/*接收状态
bit15，//接收完成标志
bit14，//接收到0x0d
bit13~0，//接收到的有效字节数目*/
u16 USART_RX_STA=0;//接收状态标记
void USART1_IRQHandler(void)
{
	/*u16 RES;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET){
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		RES=USART_ReceiveData(USART1);
		if(RES=='o'&&state==0){
			GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
			state=1;
		}if(RES=='c'&&state==1){
			GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
			state=0;
		}
	}*/
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
		res=USART_ReceiveData(USART1);
		if((USART_RX_STA&0x8000)==0)//接收未完成，&0x8000是为了判断最高位是否为1
		{
			if(USART_RX_STA&0x4000)//判断是否接收到了0x0d,接收到了0x0d那么最高位的下一位会变为1
			{
				
				if(res!=0x0a){
					USART_RX_STA=0;//接收错误，重新开始
					
				}
				else USART_RX_STA|= 0x8000;//接收完成，给最高位置1
				if(strcmp(USART_RX_BUF,"o")==0){
					GPIO_ToggleBits(GPIOB, GPIO_Pin_10);	
				}
			}
			else
			{
				n++;
				if(res==0x0d)USART_RX_STA|= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0x3FFF]=res;//&0x3FFF将最高两位清零
					USART_RX_STA++;
				}
				if(USART_RX_STA>50-1)USART_RX_STA=0;//接收数据长度不能大于USART_REC_LEN-1
			}
		
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
