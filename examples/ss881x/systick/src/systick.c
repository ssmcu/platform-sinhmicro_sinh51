/*
* Systick.c
* Systick configure and use.
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

static unsigned int systick_interrupt_flag;             /* Systick start count */
static unsigned int systick_interrupt_counter;          /* Systick count */

void systick_init(void)
{
        RCCON |= (1<<0);                                /* Enable HIRC */
        while (!(RCCON & 0x02));                        /* Waiting for stable */			
	
        TICKCON |= (5 << 5);                            /* Cycle set 10ms-0/20ms-1/50ms-2/100ms-3/200ms-4/500ms-5/800ms-6/1000ms-7 */
        TICKCON |= (1 << 0);                            /* Enable Systick */
	
        INTEN2 |= (1 << 5);                             /* Enable Interrupt Systick */
        INTEN0 |= (1 << 7);                             /* Enable Globol Interrupt */
}

void systick_delay(unsigned int time)
{
        systick_interrupt_flag = 1;		        /* start count */
        while (systick_interrupt_counter/time != 1);	/* wait count++ */
        systick_interrupt_flag = 0;
        systick_interrupt_counter = 0;                  /* clear for next */
}

void main(void)
{
        WDTCON = 0x05;                  /* disable watchdog at startup */
        
        systick_interrupt_flag = 0;
        systick_interrupt_counter = 0;
	
        P0MOD &= ~(0x03 << 0);               /* Init P00,P01 on Output */
	
        systick_init();
	
        while (1){
                P0DAT ^= (1 << 1);        /* Toggle P01 */
                systick_delay(5);		
        }
}

#if defined(__C51__)                    /* keil C51 compiler */
void systick_ISR(void) interrupt 13
#else                                   /* SDCC compiler */
void systick_ISR(void) __interrupt 13
#endif
{
        P0DAT ^= (1 << 0);                /* Toggle P00 */
	
        if (systick_interrupt_flag == 1)
                systick_interrupt_counter++; 
}