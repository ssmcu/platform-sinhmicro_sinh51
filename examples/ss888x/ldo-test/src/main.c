/*
 * main.c
 *
 * ldo-test.
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

/*LDO输出电压VSET选择	1.8V：0x0	2.5V：0x1	3.0V：0x2	3.3V：0x3 */
#define VSET 	(0x0)

/*LDO过流电流OCISET选择	60mA：0x0	80mA：0x1	100mA：0x2	120mA：0x3 */
#define OCISET	(0x2)

void ldo_init(void)
{
	EFR_ADR		 =  LDO_SFR;		/* EFR地址寄存器选中LDO_SFR寄存器地址 */
	EFR_DAT		&= ~(1 << 7);		/* 过流检测为正常模式 */
	EFR_DAT		|=  (1 << 3);		/* 开启瞬态响应优化 */
	
	EFR_ADR		 = LDO_CTL;			/* EFR地址寄存器选中LDO_CTL寄存器地址 */
	EFR_DAT		&= 0xf0;			/* 低4位清0 */
	EFR_DAT		|= (VSET	<< 2);	/* 输出电压选择 */
	EFR_DAT		|= (OCISET  << 0);	/* 过流电流选择60mA */
	EFR_DAT		|= (0x3 	<< 5);	/* 使能过流保护，使能BGR基准 */
	
	EFR_DAT		|= (1 << 7);		/* 使能LDO */
}

void led_init(void)
{
	P1MOD &= ~(1 << 0);				/* 配置P10为输出模式 */
	P1DAT &= ~(1 << 0);				/* 配置P10默认输出低电平，默认灭LED */
}

int main()
{	
    WDTCON  = 0x05;					/* 关闭看门狗 */
	
	led_init();
    ldo_init();
    
    while (1) {
		EFR_ADR	= LDO_SFR;			/* 选中LDO_SFR寄存器地址，为了检测过流标志位 */
		if (EFR_DAT & (1 << 1)) {	/* 发生过流保护时 */
			P1DAT |= (1 << 0);		/* P10所连接的LED灯亮 */
		}
	}
}
