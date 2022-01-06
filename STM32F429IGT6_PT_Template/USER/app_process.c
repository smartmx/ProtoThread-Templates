#include "protothread.h"

/* app_process每秒钟打印一次 */
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

/* app_process2每0.66秒钟打印一次 */
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

/*app_process3展示如何实现和freertos中delay一样类似的作用 */
PROCESS(app_process3,"app_process3");

PROCESS_THREAD (app_process3, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();

    printf("app_process3 begin\n");
    while(1){
        printf("app_process3 wait 1 second\n");
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        printf("app_process3 wait 2 second\n");
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 2);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        printf("app_process3 wait 3 second\n");
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS * 3);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    }
    PROCESS_END();
}
