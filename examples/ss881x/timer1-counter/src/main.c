/*
 * timer1-count.c
 *
 * TIMER1 test.
 *
 * Author: zhanyingwei<3080940495@qq.com>
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

#define COUNTER (10)         //脉冲个数

typedef unsigned char u8;
typedef unsigned int u16;

void timer1_init()
{     
    TMOD = 0x40;                  // Timer1 13bit model
    TL1  = 0x00;                  // 设置低5位初值(只使用低5位)
    TH1  = 0x00;                  // 设置高8位初值
    ET1  = 1;                     // enable ET1 IRQ
    EA   = 1;                     // Enable global IRQ
    TR1  = 1;                     // start-up Timer1
}

void pulse_counter(u16 number)     // 通过P02输出脉冲提供给P13
{
    u16 i=0;
    number  = 2 * number;
    
    for(i=0;i<number;i++)
    {
        P0  ^= 0x04;       //P02状态翻转
    }
}

int main()
{
    WDTCON  = 0x05;         // disable watchdog at startup
   
    P0MOD  &= ~0x04;       // P02 as GPIO output
    
    MFP2   &= ~0xC0;
    MFP2   |= 0xC0;       // P13 as T1
    
    timer1_init();
    pulse_counter(COUNTER);
    
    while (1) {
    }
}

