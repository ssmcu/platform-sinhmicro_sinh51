/*
 * eint0-test.c
 *
 * EINT0 test.
 *
 * Author: lipeng<lp@sinhmicro.com>
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

typedef unsigned char u8;
typedef unsigned int u16;

void Timer0Init()
{
    TCON1 |= 0x08;         //TCLK0=SCLK/2=2MHz       
    TMOD  |= 0x02;         //Timer0 8bit reload model
    TL0  = 0x38;           //计数值
    TH0  = 0x38;           //装载值
    ET0  = 1;              // enable ET0 IRQ
    EA   = 1;              // Enable global IRQ
    TR0  = 1;              //start-up Timer0
    
}

int main()
{
    WDTCON  = 0x05;         // disable watchdog at startup

    P0MOD  &= ~0x01;       // P00 as GPIO output
    P0     &= ~0x01;       // P00 output low
    
    Timer0_Init();
    while (1) {
    }
}
void Timer0() interrupt 1
{
    static u16 i;
    i++;
    if(i==10000)            //每隔1s,P00翻转一次
    {
        P0  ^= 0x01;
        i  = 0;    
    }
}

