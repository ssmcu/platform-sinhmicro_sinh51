/*
 * time2-capture
 *
 * Use the capture function of timer 2 to measure the frequency of a wave.
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

static unsigned long int tcch, tcc[10], cycle[9];

void pwm0_init()
{
    MFP0  = (MFP0 & 0xfc) | 0x01;           /* P00作为PWM0 */
    TCON1 = 0x08;                           /* 分频系数/6 */
    TMOD  = 0x02;
    TL0   = 0X38;                           /* 计数值 */
    TH0   = 0X38;                           /* 装载值 */
    TPDL0 = 0x9c;
    TPE0  = 1;
    TR0   = 1;
}

void cc0_init()
{
    MFP0   = (MFP0 & 0xcf) | 0x30;           /* P02作为CC0 */
    T2CON  = 0x80;                           /* 分频系数/6 */
    TL2    = 0xc0;                           /* 计数值 */
    TH2_0  = 0x00;
    TH2_1  = 0x00;
    TRL2   = 0xc0;                           /* 装载值 */
    TRH2_0 = 0x00;
    TRH2_1 = 0x00;
    T2MOD  = 0x05;                           /* TCCM0启动捕获功能 */
    TCCS0  = 1;
    TR2    = 1;
}

void main()
{
    char i, j;
    
    WDTCON = 0x05;                           /* 关闭看门狗 */
    
    cc0_init();
    pwm0_init();
    
    i = 0;
    while (i < 10) {                
        if (T2STAT & 0x01) {                 /* 如果捕获到，则将其放在tcc数组中 */
            T2STAT  = 0x00;
            tcch    = TCC0H & 0x1f;
            tcc[i]  = (tcch << 8) | TCC0L;
            i++;
        }
    }
    
    j = 0;
    while (j < 9) {                            /* 将计算的周期放到cycle中 */
        cycle[j] = 2000000 / (tcc[j+1] - tcc[j]);
        j++;
    }
    
    while (1) {
    
    }
}









