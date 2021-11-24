/*
 * low-speed-test.c
 *
 * low-speed-test.
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


void main()
{
        WDTCON   = 0x05;   /* 关闭看门狗 */
        CLKCON0 |= 0x01;   /* 开启高频，SCLK为12M Hz */
        CLKCON0 &= 0xF1;   /* 分频系数为1 */

        delay_ms(500);    /* 延迟等待高频稳定 */

        CLKCON0 &= 0xFE;   /* 关闭高频，开启低频 */
        RCCON   &= 0xFE;   /* 关闭高频使能位 */
        CKCON   |= 0x00;   /* 程序访问等待周期为1 */

}

