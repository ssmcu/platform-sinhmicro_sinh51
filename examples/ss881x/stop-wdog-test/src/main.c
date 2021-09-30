/*
 * stop_wdog.c
 *
 * WATCHDOG test.
 *
 * Author: Zhanyingwei<3080940495@qq.com>
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

void _delay_ms(unsigned int m)
{	
    unsigned int i, j;
    for ( i=m; i>0; i-- )
    {
        for ( j=300; j>0; j-- );
    }
}

void flicker_light(void)
{
    /* enable watchdog wakeup source */
    CLKCON0 |= (1 << 6);                                      // 使能看门狗定时器唤醒功能
    WDTCON   = 0x2A;                                          // WDY使能,溢出时间2s,空闲状态不工作
    _delay_ms(1000);
    
    /* system enter stop mode */
    CLKCON0 &= 0xFE;                                          // SCLK源头选择低频RC(LORC) 
    RCCON &= 0xFE;                                            // 高频RC不使能 
    P0DAT &= ~0x01;                                           // P00 output low
    PCON  |= 0x02;                                            // 进入待机模式
    
    /* normal mode clock selection */
    RCCON |= 0x01;                                            // 高频RC使能 
    while (!(RCCON & 0x02));                                  // 等待高频RC稳定
    CLKCON0 |= 0x01;                                          // SCLK源头选择高频RC(HIRC)
    
    P0DAT |= 0x01;                                            // P00 output high
}

int main()
{
    CLKCON1 |= 0x08;                                          // ADC & Charge模块时钟使能
    
    /* disable all wakeup source */
    CHGCON4 &= ~(1 << 6);                                     // 不使能DCIN唤醒功能
    PWRCON0 &= ~(1 << 4);                                     // 不使能VKEY按键唤醒
    CLKCON0 &= ~(1 << 6);                                     // 不使能看门狗定时器唤醒功能
    P1MOD &= ~(1 << 5);                                       // 不使能P03唤醒
    P1MOD &= ~(1 << 6);                                       // 不使能P04唤醒
    P1MOD &= ~(1 << 7);                                       // 不使能P06唤醒
    PWKCTL = (PWKCTL & ~(7 << 0)) | (0 << 0);                 // 不使能P07唤醒
    PWKCTL = (PWKCTL & ~(7 << 3)) | (0 << 3);                 // 不使能P11唤醒
    
    P0MOD &= ~0x01;                                           // P00 as GPIO output
    P0DAT |= 0x01;                                            // P00 output high

    while (1) {
        flicker_light();
        WDTCLR = 1;                                           // 喂狗
    }
}
