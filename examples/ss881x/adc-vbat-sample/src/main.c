/*
 * adc-vbat-sample.c
 *
 * ADC test.
 *
 * Author: zhanyingwei<3080940495@qq.com>
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

typedef unsigned char u8;
typedef unsigned int u16;

short  vbat_mv;

void adc_init()
{
    ADCCON0  = 0x28;                  // 连续模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数128
    CLKCON1  |= 0x08;                 // 送SCLK给ADC,ADC时钟使能
    ADCCHEN  = 0x41;                  // 电池电压检测通道使能
}

void data_vbat_read()
{
    vbat_mv  = ADCDAT0L + ((ADCDAT01H & 0x0F) << 8);                 // 取出ADC值
    vbat_mv  <<= 4;                                                  // 左移4位再右移4位，将12位补码转换成16位补码
    vbat_mv  >>= 4;
    vbat_mv  += 2600;                                                // 加上中心电平，VBAT中心电平为2600
}

int main()
{
    WDTCON  = 0x05;                   // disable watchdog at startup
    
    MFP0  = 0xC0;
    
    adc_init();
    
    while (1) {
        data_vbat_read();
    }
}

