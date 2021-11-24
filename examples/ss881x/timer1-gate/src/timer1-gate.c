/*
 * timer1-gate.c
 *
 * timer-gate test.
 *
 * Author: chenjingfan<chenjingfan@sinhmicro.com>
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

static void delay_ms(unsigned char ms)
{
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do
           {
            while (--j);
           } 
        while (--i);
     } 
    while (--ms);
}



void timer_int()
{
        CLKCON0 |= 0x01;    /* SCLK为12M Hz */
        TCON1   |= 0x00;    /* SCLK分频系数为1 */
	      CLKCON1  |= 0x08;   /* 送SCLK给ADC,ADC时钟使能 */
        TMOD     = 0x50 ;   /* 配置timer1 16bit 方式1 */
        TMOD     = 0x80 ;   /* GATE1=1 */
        TL1      = 0x00;
        TH1      = 0x00;
        TR1      = 1 ;      /* 打开timer1 */
}


void main()
{
        WDTCON = 0x05 ;        /* 关闭看门狗 */

        timer_int();

        MFP0 |= 0x80 ;         /* p03 作为EINT1 */
        P0MOD = 0x40 ;         /* p03配置输入模式 */

        P0MOD &= ~(0x04) ;     /* P02配置为输出模式 */
        P0DAT &= ~(0x04);      /* P02 输出 0 */
        delay_ms(500);
        P0DAT |= 0x04;         /* P02 输出 1 */

}





