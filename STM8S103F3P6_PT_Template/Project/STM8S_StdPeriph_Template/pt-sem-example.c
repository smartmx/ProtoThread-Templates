#include "protothread.h"

extern void uart1_send_string(uint8_t *str,uint8_t len);

/*
 * 定义信号量
 */
process_sem_t received, sended;

PROCESS(sem_received_process,"sem_received_process test");

PROCESS(sem_send_process,"sem_send_process test");

PROCESS_THREAD (sem_received_process, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    printf("sem_received_process begin\n");
    while(1){
        PROCESS_SEM_WAIT(&received);
        uart1_send_string("received\n",9);
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));//等待一秒钟再发送信号量
        uart1_send_string("etimer ev\n",10);
        PROCESS_SEM_SIGNAL(&sem_send_process, &sended);
    }
    PROCESS_END();
}

PROCESS_THREAD (sem_send_process, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    printf("sem_send_process begin\n");
    while(1){
        PROCESS_SEM_SIGNAL(&sem_received_process, &received);//发送方先发送信号量
        PROCESS_SEM_WAIT(&sended);
        uart1_send_string("sended\n",7);
        etimer_set(&et,PROTOTHREAD_CLOCK_SECONDS);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        uart1_send_string("etimer ev\n",10);
    }
    PROCESS_END();
}

void pt_sem_test(void)
{
    PROCESS_SEM_INIT(&sended, 0);
    PROCESS_SEM_INIT(&received, 0);
    process_start(&sem_received_process, NULL);
    process_start(&sem_send_process, NULL);
    //PROCESS_SEM_SIGNAL(&sended);
}
