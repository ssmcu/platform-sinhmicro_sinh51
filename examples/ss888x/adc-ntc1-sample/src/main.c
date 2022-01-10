/*
 * main.c
 *
 * adc-ntc1-sample.
 *
 * Author: qiujunling<qiujunling@sinhmicro.com.cn>
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

#include "ss888x.h"

/*	NTC1电流档位: 20、100(uA) */
#define NTC1ISET (20u)

short ntc1_mv;
float ntc1_kr;

void ntc1_init()
{       
	MFP0    |= (0x3 << 2);  /* 配置P01为AN3通道 */

	CLKCON1 |= (1 << 3);	/* ADC时钟使能 */

	ADCCON0  =  0x28;		/* 连续模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数128 */
	ADCCON2 &= ~(1 << 4);	/* 中心电平选择1.5V */
	ADCCHEN |=  (1 << 3);	/* AN3通道使能 */

	EFR_ADR  = 0x60;		/* 扩展功能寄存器写入LDOCON0地址 */
	EFR_DAT |= (0x3<<4);	/* 使能LDOCON0寄存器的BGREN、IBIASEN */
	
#if (NTC1ISET == 20)		/* NTC1内部电流源档位选择 */
	NTC_CTL &= ~(1 << 2);	/* 20uA */
#else
	NTC_CTL |=  (1 << 2);	/* 100uA */
#endif

	NTC_CTL &= ~(1 << 1);	/* NTC1输出到P01（AN3） */
	NTC_CTL |=  (1 << 0);	/* NTC1电流源使能 */
}

void data_read()
{
	ntc1_mv		  = ADCDAT3L + ((ADCDAT23H & 0xF0) << 4);	/* 通道3低8位加上ADCDAT23H的通道3高4位组成12位 */
	ntc1_mv		<<= 4;                                	 	/* 左移4位再右移4位，将12位补码转换成16位补码 */
	ntc1_mv		>>= 4;
	ntc1_mv		 += 1500;                              		/* 加上中心电平，VBAT中心电平为1500 */
	ntc1_kr		  = (float)ntc1_mv / NTC1ISET;				/* R(KΩ)=Vanx(mV)/电流(uA) */
}

int main()
{
	WDTCON  = 0x05;			/* 关闭看门狗 */
	
	ntc1_init();
	
	while(1) {
		data_read();		/* 数据读取 */
	}
}

