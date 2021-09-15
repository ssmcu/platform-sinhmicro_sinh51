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

#define EINT1_PIN_USED (0x03)   //0x03: reuse P03;  0x14: reuse P14

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
void eint1_ISR(void) interrupt 2
#else                       // SDCC compiler
void eint1_ISR(void) __interrupt 2
#endif
{
    
    P0 ^= 0x01;             // P00 toggle
    
    _delay_ms(250);
    
    EINTCON &= ~0x02;       // clear IE1
}

int main()
{
    WDTCON  = 0x05;         // disable watchdog at startup

    P0MOD   &= ~0x01;       // P00 as GPIO output
    P0      &= ~0x01;       // P00 output low
    
#if (EINT1_PIN_USED == 0x03)
    MFP0    |= 0x80;        // P03 as EINT1
#elif (EINT1_PIN_USED == 0x14)
    MFP3    |=30;         // P14 as EINT1
#endif

    EINTCON = 0xA0;         // EINT1 rise edge
    EX1     = 1;            // enable EINT1 IRQ

    EA      = 1;            // Enable global IRQ

    while (1) {
    }
}
