/*
 * sleep-test.c
 *
 * sleep-test.
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

#include "ss882x.h"

typedef unsigned short  uint16_t;


void delay_ms(uint16_t ms)
{
    uint16_t delay;

    while (ms--) {
        delay = 270;
        while (delay--);
    }
}

void sleep_enable()
{
   CLKCON0 |= 0x80; 
}

void main()
{
        WDTCON = 0x01;           /* 关闭看门狗 */
        CLKCON0 |= 0x01;         /* 开启高频，SCLK为6M Hz */
        CLKCON0 &= 0xF9;         /* 分频系数为1 */
	      delay_ms(1);
		    MFP0  = 0x00;            /* P00,P02作为GPIO口 */
	      P0OE |= 0x01;            /* P00输出使能 */
	      P0IE |= 0x04;            /* P02输入使能 */
	      P0_0 = 0;
				P0PUPD |= 0x40;          /* P02 上拉使能 */
	      while (1)
			  {
          while (P0_2) {
             P0_0 = 1;
					}
      			sleep_enable();
	    	}
}

