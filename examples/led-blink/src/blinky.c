/*
 * blinky.c
 *
 * LED blink test.
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

#if defined(__C51__)    /* keil C51 */
sfr             WDTCON  = 0x86;
sfr             P0      = 0x80;
sfr             P0MOD   = 0x95;
#elif defined(__SDCC)   /* SDCC */
__sfr __at 0x86 WDTCON;
__sfr __at 0x80 P0;
__sfr __at 0x95 P0MOD;
#endif

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

int main()
{
    WDTCON = 0x05;          /* disable watchdog at startup */

    P0MOD &= ~0x01;         /* P00 as GPIO output */
    P0 &= ~0x01;            /* P00 output low */

    while(1) {
        P0 &= ~0x01;        /* P00 output low */
        _delay_ms(250);
        _delay_ms(250);

        P0 |= 0x01;         /* P00 output high */
        _delay_ms(250);
        _delay_ms(250);
    }
}