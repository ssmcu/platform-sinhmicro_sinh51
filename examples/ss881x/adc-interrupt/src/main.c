/*
 * adc-interrupt.c
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

short an2_mv;

void adc_init()
{
    CLKCON1  |= 0x08;                 // 送SCLK给ADC,ADC时钟使能
    ADCCON0   = 0x6A;                 // 单次模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数256
    ADCCHEN  |= 0x04;                 // 通道AN2使能
    ADCCON1  |= 0x40;                 // ADC中断使能
    ADCCON2  |= 0x08;                 // AN2通道中心电平为2.6V
    
    EADC  = 1;                       // 打开ADC中断
    EA    = 1;                       // 打开总中断
}

void data_an2_read()
{
    an2_mv  = ADCDAT2L + ((ADCDAT23H & 0x0F) << 8);                 // 取出ADC值
    an2_mv  <<= 4;                                                  // 左移4位再右移4位，将12位补码转换成16位补码
    an2_mv  >>= 4;
    an2_mv  += 2600;                                                // 加上中心电平2600
}

int main()
{
    WDTCON   = 0x05;                   // disable watchdog at startup
    
    P0MOD   &= ~0x01;                 // P00 as GPIO output
    P0      &= ~0x01;                 // P00 output low

    P1MOD   &= ~0x08;                 // P13 as GPIO output
    P1OM    &= ~0x08;                 // P13 as PP model
    P1DAT   |= 0x08;                  // P13 output high
    
    MFP0     = 0xC0;                  // 复用P03为AN2
    
    adc_init();
    
    ADCCON0 |= 0x80;                  // 开始采样数据
    
    while (1) {
    }
}

#if defined(__C51__)        // keil C51 compiler
void adc_ISR(void) interrupt 7
#else                       // SDCC compiler
void adc_ISR(void) __interrupt 7
#endif
{
    data_an2_read();
    
    P0       |= 0x01;                 // P00 output high
    ADCCON1  &= ~0x01;                // 手动清0 ADCIF
    ADCCON0  |= 0x80;                 // 开始采样数据
}
