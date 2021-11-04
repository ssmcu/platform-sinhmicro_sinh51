/*
* pwm_deadzone.c
* PWM AND DEAD ZONE CONFIG.
*
* Copyright (C) 2021 Sinh Micro, Inc.
* Author: liwanbang@sinhmicro.com.cn
*
* Changelog:
* 20211020: Init version
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

void timer2_cc_init(void)
{           
        T2MOD = 0x0a;                   /* start pompare */
        T2D2 = 0x88;                    /*set  tccx0/h  */
        T2D6 = 0x73;                    /*set  tccx0/h ， set Timer2 count */
        T2D3 = 0x88;                    /*set  tccxl/h */
        T2D7 = 0xb3;                    /*set  tccxl/h ，set  tccxl/h ， set Timer2 reload */
        T2D0 = 0x1a;                    /* set Timer2 count */
        T2D8 = 0x60;                    /* set Timer2 count */
        T2D1 = 0xa0;                    /* set Timer2 reload */
        T2D9 = 0x20;                    /* set Timer2 reload */
        T2CON = 0x01;                   /* set div from sclk ， pompare output polarity */
        T2CON |= (1 << 4);              /* start timer2 */
}


void prou_deadzone_init(void)
{       
        HPWMCON0 = 0x04;                /* enable dead zone */
        HPWMDZT0 = 0xff;                /* set DZT0 (0-15) */
        DLLCON0 = 0x03;                 /* set DLL source,enable */
        DLLCON1 = 0x0a;                 /* set DLL Freq range */
        while(! (DLLCON0&(1<<3) ) );    /* wait DLL enable */
}

void main(void)
{
        WDTCON = 0x05;                          /* disable watchdog at startup */

        RCCON |= (1 << 0);                        /* Enable HIRC */
        while ( !(RCCON & (1 << 1) ) );          /* Waiting for stable */      
        CLKCON0 = 0x07;
        
        MFP1 |= (0x01 << 0);                      
        EFRADR  =  0x12;                                                     
        EFRDAT  &= ~(0x03 << 0);
        MFP2 |= (0x03 << 0);                      /* SET CC0,CC1 in P04,P10 */

        timer2_cc_init();
        prou_deadzone_init();          
        
        while (1){

        }
}

