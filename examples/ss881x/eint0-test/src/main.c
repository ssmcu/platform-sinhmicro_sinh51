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

#define EINT0_PIN_USED 0x04   //0x04: reuse P04;  0x10: reuse P10

static void _delay_ms(unsigned char ms)
{	
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do
        {
            while (--j);
        } while (--i);
    } while (--ms);
}


#if defined(__C51__)        // keil C51 compiler
void eint0_ISR(void) interrupt 0
#else                       // SDCC compiler
void eint0_ISR(void) __interrupt 0
#endif
{
    
    P0 ^= 0x01;             // P00 toggle
    
    _delay_ms(250);
    
    EINTCON &= ~0x01;       // clear IE0
}

int main()
{
    WDTCON  = 0x05;         // disable watchdog at startup

    P0MOD   &= ~0x01;       // P00 as GPIO output
    P0      &= ~0x01;       // P00 output low
    
#if (EINT0_PIN_USED == 0x04)
    MFP1    &= ~0x03;
    MFP1    |= 0x02;        // P04 as EINT0
#elif (EINT0_PIN_USED == 0x10)
    MFP2    &=~0x03;
    MFP2    |=0x02;         // P10 as EINT0
#endif

    EINTCON = 0x20;         // EINT0 rise edge
    EX0     = 1;            // enable EINT0 IRQ

    EA      = 1;            // Enable global IRQ

    while (1) {
    }
}
