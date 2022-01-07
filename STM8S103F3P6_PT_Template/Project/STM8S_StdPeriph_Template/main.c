/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
#include "stm8s.h"
#include "delay.h"
#include "protothread.h"
#include "app_process.h"
#include "pt-sem-example.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int uart1_putc(int ch)
{
  while (((UART1->SR) & 0x80) == 0);
  UART1->DR = (uint8_t)ch;
  return ch;
}

void uart1_send_string(uint8_t *str,uint8_t len)
{
  uint8_t i = 0;
  while(i < len){
    uart1_putc(str[i]);
    i++;
  }
}

static void CLK_Init(void)  
{    
#ifdef USER_HSE
  CLK_HSECmd(ENABLE);                                   //外部时钟开    
  CLK_LSICmd(ENABLE);                                   //内部低频RC开    
  CLK_HSICmd(ENABLE);                                   //内部高频RC开   
  while(SET != CLK_GetFlagStatus(CLK_FLAG_HSERDY));    //等待外部晶振起振    
  CLK_ClockSwitchCmd(ENABLE);                           //切换使能    
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL,CLK_SOURCE_HSE,DISABLE,CLK_CURRENTCLOCKSTATE_DISABLE);//切换到外部晶振   
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);              //1分频    
#else
  CLK_HSICmd(ENABLE);//开始内部高频RC
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//不分频
#endif
}   



void main(void)
{
  CLK_Init();//启用内部16m晶振
  
  delay_init(16);//初始化延迟函数
  
  UART1_DeInit();
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
            UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  
  TIM2_DeInit();
  CLK_PeripheralClockConfig( CLK_PERIPHERAL_TIMER2, ENABLE);
 // 16分频 即 1MHz
  TIM2_TimeBaseInit( TIM2_PRESCALER_16, 1000);  //1ms一次
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
  TIM2_Cmd(ENABLE);
  
  protothread_init();
  
  enableInterrupts();
  
  uart1_send_string("protothread test\n",17);
//    process_start(&app_process, NULL);
  process_start(&app_process2, NULL);
  process_start(&app_process3, NULL);
  pt_sem_test();
  /* Infinite loop */
  while (1)
  {
    protothread_mainLoop();
  }
    
}




#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
