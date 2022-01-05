#include "protothread.h"
#include "stdio.h"

PROCESS(app_process,NULL);

PROCESS_THREAD (app_process, ev, data)
{
  static struct etimer et;
  PROCESS_BEGIN();
  printf("app_process start\r\n");
  etimer_set(&et, PROTOTHREAD_CLOCK_SECONDS * 1);
  while(1){
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_TIMER){
      printf ("protothread etimer\r\n");
      etimer_reset(&et);
    }
  }
  PROCESS_END();
}


