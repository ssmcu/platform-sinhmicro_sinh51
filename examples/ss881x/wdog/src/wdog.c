/*
 * wdog
 *
 * wdog test.
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

unsigned char idog;

static void _delay_ms(unsigned char ms)
{	
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do{
            while (--j);
        } while (--i);
    } while (--ms);
}


void main()
{                  
        
        idog = 0;
        
        WDTCON &= ~(1<<7);              /* WDOG dont work in idle */
        WDTCON &= ~(0x07<<4);
        WDTCON |= (0x02<<4);            /* set WDOG timout 2s*/
        
        
        P0MOD &= ~0x02;                 /* P01 as GPIO output */
        
        if(RESETS&(1<<4)){
                RESETS &= ~(1<<4);      /* clear reset flag */
                
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
                if(idog<20){
                        idog++;
                        RESETS |= (1<<7);      /* feed dog */
                }     
                P0 ^= 0x02;
		_delay_ms(500);	
        }
}
