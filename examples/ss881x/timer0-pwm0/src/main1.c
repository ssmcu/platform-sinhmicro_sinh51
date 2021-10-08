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
    TMOD   =  0x02;         /*�����ڶ�ʱ��0�ķ�ʽ2*/
    TCON1  =  0x08;        
	TL0    =  0x38;			/* ��ʱ�����ʱ��Ϊ100ms */	
	TH0    =  0x38;         /* װ��ֵ */
    MFP0   =  0x01;         /* ʹP00������PWM0ģʽ */
    TCON   =  0x02;         /* ����PWM0 */        
    TPDL0  =  0xff;	
	EA     =  1;            /* �ж��ܿ���ʹ�� */
	ET0    =  1;            /* ��ʱ��0���ж�ʹ��  */
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
     *ÿ��ı�PWM0�Ŀ�ռ�ȣ�ʹ����0~100%�仯
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
