/*
 * pin_reset
 *
 * p03 reset test.
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

/* Reset pin must pull up first */
/* PWRCON2 bit7:3   PWRCON4 bit4  P1MOD bit7:6  PWKCTL bit5:0  SFR  SSD */

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
        P0PU |= (1<<3);                         /* enable pull-up */
        MFP0 = (MFP0 & ~(0x03 << 6)) | (1 << 6);    /* set P03 RESET */
        
        WDTCON = 0x05;                          /* disable watchdog at startup */     
        
        P0MOD &= ~0x02;                 /* P01 as GPIO output */
        
        if(RESETS&(1<<1)){
                RESETS &= ~(1 << 1);      /* clear reset flag */
                
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
        
        while (1){
                P0 ^= 0x02;
                _delay_ms(500);	
        }
}
