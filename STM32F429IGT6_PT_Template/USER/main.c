#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "app_process.h"
#include "pt-sem-example.h"
/************************************************
 ALIENTEK 阿波罗STM32F429开发板实验0-2
 Template工程模板-调试章节使用-HAL库版本
 技术支持论坛：www.openedv.com
 淘宝店铺：    http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

/*注意：本工程和教程3.4小节程序下载调试工程对应*/

int main(void)
{
    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化USART
		printf("protothread test\n");
		protothread_init();
//    process_start(&app_process, NULL);
    process_start(&app_process2, NULL);
    process_start(&app_process3, NULL);
    pt_sem_test();

	  while(1)
	{
		protothread_mainLoop();
	}
}


