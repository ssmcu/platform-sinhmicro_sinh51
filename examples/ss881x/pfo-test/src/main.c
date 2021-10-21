/*
 * pfo-test.c
 *
 * PFO test.
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

static unsigned long count = 0;

static void _delay_ms(unsigned char cycle_number)
{	
	unsigned long radix = count;
	while(count - radix < cycle_number);
}

void main(void)
{
    WDTCON   = 0x05;                      // disable watchdog at startup
	EA       = 1;
	
	TICKCON &= ~0xE0;                     // SysTick cycle as 10ms
	INTEN2  |= 0x20;                      // SysTick Interrupt enable
	TICKCON |= 0x01;                      // enable SysTick
    
    MFP1    &= ~0xC0;
    MFP1    |= 0x80;                      // P07 as PFO
    
    CLKCON1 |= 0x10;                      // enable PFOU clock
	PRCCON0 &= ~0x10;                     // not enable PRC
    
	/** PRCFREQ = 1024; PRCDIV = 1; not adjust duty-on ratio (duty-on ratio fixed at 50%) */
    PRCCON1 &= ~0xE7;
	PRCCON1 |= 0x80;
	PRCFREQL = 0x00;
    
    while (1) {
		PRCCON0 = 0x10;                   // PRCFC = 1.7MHz and enable PRC
		_delay_ms(200);                   // delay 2s
		
		PRCCON0 = 0x50;                   // PRCFC = 2.4MHz and enable PRC
		_delay_ms(200);                   // delay 2s
		
		PRCCON0 = 0x90;                   // PRCFC = 3MHz and enable PRC
		_delay_ms(200);                   // delay 2s
    }
}

#if defined(__C51__)        // keil C51 compiler
void systick_count() interrupt 13
#else                       // SDCC compiler
void systick_count() __interrupt 13
#endif
{
	count++;
}
