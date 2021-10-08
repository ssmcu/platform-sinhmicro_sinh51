/*
 * io_test.c
 *
 * The brightness of the LED lamp is changed by changing the duty cycle of pwm0.
 *
 * Author: huxingmin<cyan1219@sina.com>
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

unsigned int count = 0,count1 = 0;

void time0_init()
{
    TMOD   =  0x02;         /*工作在定时器0的方式2*/
    TCON1  =  0x08;        
	TL0    =  0x38;			/* 定时器溢出时间为100ms */	
	TH0    =  0x38;         /* 装载值 */
    MFP0   =  0x01;         /* 使P00工作在PWM0模式 */
    TCON   =  0x02;         /* 启动PWM0 */        
    TPDL0  =  0xff;	
	EA     =  1;            /* 中断总开关使能 */
	ET0    =  1;            /* 定时器0的中断使能  */
    TR0    =  1;             
}

void main()
{
    WDTCON = 0x05;
	time0_init();
    
	while (1) {		
        
	}
    
}

#if defined(__C51__)        /* keil C51 compiler */
void timer0_ISR() interrupt 1
#else                       /* SDCC compiler */
void timer0_ISR() __interrupt 1
#endif
{
    count++;
    
    /* 
     *每秒改变PWM0的空占比，使其在0~100%变化
     */
    if (count == 10000) {   
        count = 0;
        TPDL0 = TPDL0 << 1;
    }
    
    if (TPDL0 < 0x38) {    
        count1++;
        if (count1 == 10000) {
            TPDL0 = 0xff;
            count1 = 0;
        }
    }
    
}
