/*
 * stop-test.c
 *
 * stop-test.
 *
 * Author: chenjingfan<919419355@qq.com>
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
typedef unsigned short  uint16_t;


void delay_ms(uint16_t ms)
{
    uint16_t delay;

    while (ms--) {
        delay = 270;
        while (delay--);
    }
}


int main()
{
        WDTCON   = 0x05;   /* 关闭看门狗 */
        CLKCON0 |= 0x01;   /* 开启高频，SCLK为12M Hz */
        CLKCON0 &= 0xF1;   /* 分频系数为1 */

        delay_ms(500);

        /* 关闭所有唤醒源 */
        CHGCON4 &= ~(1 << 6);
        PWRCON0 &= ~(1 << 4);
        CLKCON0 &= ~(1 << 6);
        P1MOD   &= ~(1 << 5);
        P1MOD   &= ~(1 << 6);
        P1MOD   &= ~(1 << 7);
        PWKCTL   = (PWKCTL & ~(7 << 0)) | (0 << 0);
        PWKCTL   = (PWKCTL & ~(7 << 3)) | (0 << 3);

        MFP0  &= ~(0xC0);     /* p03功能选择 */
        P0MOD  = 0x08;        /* p03 选择输入模式 */
        PCON  &= ~(0x80);    /* p03作为唤醒源 */
        P1OM   = 0x20 ;        /* p03高电平唤醒 */
        P1MOD  = 0x20;        /* p03唤醒使能 */	
        P0_1 = 0;

        delay_ms(500);
        CLKCON0 &= 0xFE;     /* 开启低频 */   
        PCON |= 0x02;        /* 开启待机模式 */
       
        /* 等待唤醒 */ 
        while (1) {
          P0_1 = 1;
        }	   
}

