/*
 * cmp-test
 *
 * Analog comparator comparison and interrupt function.
 *
 * Author: huxingmin<cyan1219@sina.com>
 * 
 * Copyright (C) 2021 Sinh Micro, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "ss881x.h"

void cmp_init()
{
    MFP1    = 0X03;                                   /* P04作为CMP1负端 */
    CLKCON1 = 0X04;                                   /* 系统时钟使能 */
    CMPCON0 = 0Xf0;                                   /* 比较器1使能，正端电压1.5v */
    CMPCON1 = 0X10;                                   /* 比较器输出状态 Debounce 时间 */
    CMPCON2 = 0X30;                                   /* 结果变化产生中断 */
    ECMP    = 1;
    EA      = 1;
}

void delay_ms(unsigned int t)
{
    unsigned int delay;
    
    while (t--) {
        delay = 240;
        
        while (delay--);
    }
}

void main()
{
    WDTCON = 0X05;                                    /* 关看门狗 */
    P0MOD  &= ~(1 << 0);                              /* P00作为输出 */
    P0MOD  &= ~(1 << 2);                              /* P02作为输出 */
    
    cmp_init();
    
    while (1) {
       delay_ms(100);                                 /* 延时100ms */
        
       P0_0 = 1;
        
       delay_ms(100);                                 /* 延时100ms */
        
       P0_0 = 0;
    }
}


#if defined(__C51__)        // keil C51 compiler
void eint0_ISR(void) interrupt 7
#else                       // SDCC compiler
void eint0_ISR(void) __interrupt 7
#endif
{
    P0_2 ^= 1;                                       /* 第一次进入中断P02 = 0;第二次进入中断P02 = 1 */ 
    CMPCON2 = CMPCON2 & 0x7f;
}












