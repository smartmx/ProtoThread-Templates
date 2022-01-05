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

PROCESS(app_process,"app_process");

PROCESS_THREAD (app_process, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 1);
    printf("app_process begin\n");
    while(1){
        PROCESS_WAIT_EVENT();
        if(ev == PROCESS_EVENT_TIMER){
            printf ("app_process etimer\r\n");
            etimer_reset(&et);
        }
    }
    PROCESS_END();
}

PROCESS(app_process2,"app_process2");

PROCESS_THREAD (app_process2, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 2 / 3 );
    printf("app_process2 begin\n");
    while(1){
        PROCESS_WAIT_EVENT();
        if(ev == PROCESS_EVENT_TIMER){
            printf ("app_process2 etimer\r\n");
            etimer_reset(&et);
        }
    }
    PROCESS_END();
}

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
    process_start(&app_process, NULL);
    process_start(&app_process2, NULL);
    printf("Enter main loop.\n");
	while(1)
	{
	    protothread_mainLoop();
	}
}
