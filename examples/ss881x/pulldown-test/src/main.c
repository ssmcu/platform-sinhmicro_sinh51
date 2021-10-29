/*
 * pulldown-test
 *
 * Measurement of pull-down resistance.
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

void delay_ms(unsigned int t)
{
    unsigned int delay;
    
    while (t--) {
        delay = 240;
        
        while (delay--);
    }
}

void main()
{
    WDTCON  = 0X05;                     /* �ؿ��Ź� */

    P0MOD  |=  (0X1 << 1);              /* ��P01��Ϊ���� */

    while (1) {
        P0PD  |=  (0X1 << 1);           /* ��P01����ʹ�� */
        delay_ms(1000);                 /* ��ʱ1s */
        P0PD  &=  ~(0X1 << 1);          /* ��P01��ֹ���� */
        delay_ms(1000);                 /* ��ʱ1s */
    }
}






















