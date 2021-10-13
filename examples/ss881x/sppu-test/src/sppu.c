/*
 * sppu-test
 *
 * When the high level is measured from p12, trigger the protection to make P02 output low level..
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

void cc0_compare_init()
{
    MFP0    =  (MFP0 & 0XCF) | 0X30;            /* P02��Ϊcc0�� */
    T2CON   =  0X80;                            /* ��Ƶϵ��/6 */
    T2MOD   =  0X02;                            /* �����ȽϹ��� */
    TL2     =  0XC0;                            /* ����ֵ */
    TH2_0   =  0X00;
    TH2_1   =  0X00;
    TRL2    =  0XC0;                            /* װ��ֵ */
    TRH2_0  =  0X00;
    TRH2_1  =  0X00;
    TCC0L   =  0XFF;                            /* ����PWMռ�ձ� */
    TCC0H   = (TCC0H & 0XE0) | 0X1F;
    TR2     =  1;
}

void sppu0_init()
{
    EFRADR  =  0X12;                            /* P12��ΪSPPTRIG */                             
    EFRDAT  =  0X02;
    EFRADR  =  0X50;                            /* ��P12����Ϊ�ⲿ����ߵ�ƽ�������� */
    EFRDAT  =  0X18;
    EFRADR  =  0X51;                            /* ���ô�������ʱcc0����͵�ƽ */
    EFRDAT  =  0X01;
    
}

void delay_50ms()
{
    unsigned int i = 50000;
    
    while (i > 0) {
        i--;
    }
}
void main()
{
    WDTCON  = 0X05;
    P1PUPD  = 0X04;                             /* ��P12��ʼ��ƽ���ͣ���ֹ���� */
    
    cc0_compare_init();
    sppu0_init();
    
    while (1) {
        delay_50ms();
        TCC0H  = (TCC0H & 0XE0) | 0X0F;        /* �ı�TCC0H�Ӷ�ʹPWM��ռ��Ϊ51%��ʹ���� */
      
        delay_50ms();                          /* ��ʱ50ms */
        TCC0H  = (TCC0H & 0XE0) | 0X1F;        /* �ı�TCC0H�Ӷ�ʹPWM��ռ��Ϊ0��ʹ���� */
    }
}
    

























