/*
 * adc-i-sample.c
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



void adc_init()
{  
        ADCCON0  |= 0x28;      /* 连续模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数128 */      
        CLKCON1  |= 0x08;      /* 送SCLK给ADC,ADC时钟使能 */
        ADCCHEN   = 0x20;      /* AN5通道使能 */
        ADCCON3  &= ~(0x02);   /* ADCCCON3的 bit1写0 */
}


void data_i_read()
{
        int   R = 1000;                         /*  采样电阻的值为1Ω */
        short  i_ma;
        i_ma    = ADCDAT5L;
        i_ma   += ((ADCDAT45H & 0xF0) << 4);
        i_ma  <<= 4;                            /* 左移4位再右移4位，将12位补码转换成16位补码 */
        i_ma  >>= 4;
        i_ma    = i_ma / 36 / R;                 /* 实际计算过程，根据R大小简化计算过程 */
}

int main()
{
        WDTCON  = 0x05;   /* 关闭看门狗 */
        MFP2    = 0x0C;   /* p11 作为 AN5 */
			
        adc_init();
    
        while(1) {
           data_i_read();
        }
}

