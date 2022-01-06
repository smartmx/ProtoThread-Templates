/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*******************************************************************************/
#include "debug.h"
#include "protothread.h"
#include "main.h"
#include "app_process.h"
#include "pt-sem-example.h"
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	Delay_Init();
	USART_Printf_Init(115200);
    protothread_init();

//    process_start(&app_process, NULL);
//    process_start(&app_process2, NULL);
//    process_start(&app_process3, NULL);
    pt_sem_test(); //信号量测试初始化
	while(1)
	{
	    protothread_mainLoop();
	}
}
