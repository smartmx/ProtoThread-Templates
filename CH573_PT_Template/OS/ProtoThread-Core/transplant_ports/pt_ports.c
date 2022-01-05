/*
 * Copyright (c) 2022, mx1117 - smartmx@qq.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "protothread.h"

clock_time_t ptTicks = 0;

/*********************************************************************
 * @fn      protothread_clock_init
 *
 * @brief   ProtoThread心跳时钟初始化，如果在外边自行实现了定时器初始化，则该函数可以为空
 *
 * @param   None.
 *
 * @return  None.
 */
void protothread_clock_init(void)
{
  ptTicks = 0;
  printf("systick:%d\n",GetSysClock());
  SysTick_Config(GetSysClock() / PROTOTHREAD_CLOCK_SECONDS);
}

/*********************************************************************
 * @fn      protothread_clock_time
 *
 * @brief   获取心跳时钟的值
 *
 * @param   None.
 *
 * @return  clock_time_t 心跳时钟的值.
 */
__attribute__((section(".highcode")))
clock_time_t protothread_clock_time(void)
{
  return ptTicks;
}

__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
void SysTick_Handler(void)
{
  if( SysTick->CNTFG & 0x00000002 ){
    ptTicks++;
    if(etimer_pending() && etimer_next_expiration_time()<= ptTicks)
    {
      etimer_request_poll();
    }
    SysTick->CNTFG &= ~0x00000002;
  }
}

