/*
 * lvr_reset
 *
 *
 * Author: <liwanbang@sinhmicro.com.cn>
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

/*  检测使能：PWRCON2 bit0
 *  检测门限：PWRCON2 bit5:3
 *  检测中断: PWRSTAT bit4 
 *　　
 *  重启使能：PWRCON2 bit2
 *　重启门限：PWRCON2 bit7:6
 */

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


void main()
{                  
        WDTCON = 0x05;                  /* disable watchdog at startup */
        
        PWRCON2 &= ~(0x03 << 6);        /* set low voltage reset value to 3.85v */
        PWRCON2 &= ~(0x07 << 3);          
        PWRCON2 |= ~(0x02 << 3);        /* set low voltage detect value to 4.1v */
        PWRCON2 |= (1 << 0);            /* enable low voltage detect */
        PWRCON2 |= (1 << 2);            /* enable low voltage reset */
   
        P0MOD &= ~0x02;                 /* P01 as GPIO output */
        P0 &= ~0x02;

        if (RESETS & (1 << 3)) {        /* read low voltage reset flag */
                RESETS &= ~(1 << 3);    /* clear reset flag */
                
                P0MOD &= ~0x01;         /* P00 as GPIO output */
                P0 &= ~0x01;
                      
                _delay_ms(500); 
                P0 ^= 0x01;        
                _delay_ms(500);
                P0 ^= 0x01;        
                _delay_ms(500);
                P0 ^= 0x01;        
                _delay_ms(500);
                P0 ^= 0x01;        
                _delay_ms(500);
        }
        
        while (1) {    
                P0 ^= 0x02;
                _delay_ms(500);	
        }
}
