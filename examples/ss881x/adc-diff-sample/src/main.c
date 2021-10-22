/*
 * adc-diff-sample
 *
 * ADC differential current measurement.
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
#define R_sampling  (100)                       /* 采样电阻R = 100m Ω */

static int v_ma, i_ma;                          /* i_ma为通过电阻R的电流 */ 

void adc_init()
{
    MFP1    = 0X30;                             /* P06作为AN4 */
    MFP2    = 0X0C;                             /* P11作为AN5 */
    CLKCON1 |= 0X08;                            /* ADC模块系统时钟使能 */
    ADCCON0 = 0X3C;                             /* 采样时钟2MHZ，滤波512级 */
    ADCCHEN = 0X30;                             /* AN4,AN5通道开启，其它通道关闭 */
    ADCCON2 = 0X01;                             /* 使能差分模式 */
}

#if (R_sampling == 100)
void adc_val()
{   
    short adcval = ADCDAT4L + ((ADCDAT45H & 0X0F) <<8);
    adcval       = adcval << 4;
    adcval       = adcval >> 4;
    v_ma         = adcval;
    i_ma         = (((v_ma << 2) + v_ma) >> 1) / 9;          
}
#endif

void main()
{
    WDTCON = 0X05;                              /* 关闭看门狗 */
    
    adc_init();
    while (1) {
        adc_val();
    }
}

























