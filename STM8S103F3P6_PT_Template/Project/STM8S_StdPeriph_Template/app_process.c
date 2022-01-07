#include "protothread.h"

extern void uart1_send_string(uint8_t *str,uint8_t len);

/* app_process每秒钟打印一次 */
PROCESS(app_process,"app_process");

PROCESS_THREAD (app_process, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 1);
    uart1_send_string("app_process begin\n",18);
    while(1){
        PROCESS_WAIT_EVENT();
        if(ev == PROCESS_EVENT_TIMER){
            uart1_send_string ("app_process etimer\n",19);
            etimer_reset(&et);
        }
    }
    PROCESS_END();
}

/* app_process2每0.66秒钟打印一次 */
PROCESS(app_process2,"app_process2");

PROCESS_THREAD (app_process2, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 2 / 3 );
    uart1_send_string("app_process2 begin\n",19);
    while(1){
        PROCESS_WAIT_EVENT();
        if(ev == PROCESS_EVENT_TIMER){
            uart1_send_string ("app_process2 etimer\n",20);
            etimer_reset(&et);
        }
    }
    PROCESS_END();
}

/*app_process3展示如何实现和freertos中delay一样类似的作用 */
PROCESS(app_process3,"app_process3");

PROCESS_THREAD (app_process3, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();

    uart1_send_string("app_process3 begin\n",19);
    while(1){
        uart1_send_string("app_process3 wait 1 second\n",27);
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        uart1_send_string("app_process3 wait 2 second\n",27);
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 2);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        uart1_send_string("app_process3 wait 3 second\n",27);
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 3);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    }
    PROCESS_END();
}
