/*
 * adc-ntc-sample.c
 *
 * ADC test.
 *
 * Author: chenjingfan<919419355@qq.com>
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

short  vbat_mv;


void adc_init()
{
        CLKCON1 |= 0x08;       /* 送SCLK给ADC,ADC时钟使能 */
        ADCCON0  = 0x28;       /* 连续模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数128 */
        ADCCHEN |= 0x04;       /* AN2通道使能 */
        ADCCON1  = 0x10;       /* NTC使能 */
        ADCCON2  = 0x08;       /* 中心电平选择2.6V */
}

void data_read()
{
        vbat_mv    = ADCDAT2L + ((ADCDAT23H & 0x0F) << 8);
        vbat_mv  <<= 4;                                   /* 左移4位再右移4位，将12位补码转换成16位补码 */
        vbat_mv  >>= 4;
        vbat_mv   += 2600;                                /* 加上中心电平，VBAT中心电平为2600 */
}

int main()
{
        WDTCON  = 0x05;     /* 关闭看门狗 */                 
        MFP0    = 0xC0;     /* P03作为AN2通道 */
    
        adc_init();
    
        while(1) {
           data_read();
        }
}

