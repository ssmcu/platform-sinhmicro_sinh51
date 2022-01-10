/*
 * main.c
 *
 * data-flash-test.
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

void data_flash_read(unsigned char addr, unsigned char num, unsigned char *dat)
{
	unsigned char i = 0;
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT |= (0x1 << 0);			/* 使能读 */
	while(i<num){
		EFR_ADR  = EEADR;			/* EFR_ADR寄存器写入EEADR地址 */
		EFR_DAT  = addr + i;		/* 写入目标地址,i为偏移量 */
		EFR_ADR  = EECTL;			/* EFR_ADR寄存器写入EECTL地址 */
		EFR_DAT |= (1 << 2);		/* 将RD置1，激活读周期 */
		while(EFR_DAT & (1 << 2));	/* 等待RD清0 */
		EFR_ADR  = EEDAT;			/* EFR_ADR寄存器写入EEDAT地址 */
		*(dat + i) = EFR_DAT;		/* 读取数据 */
		i++;
	}
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT &= ~(0x3 << 0);			/* 清0RWEN */
}

void data_flash_write(unsigned char addr, unsigned char num, unsigned char *dat)
{
	unsigned char i = 0;
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT |= (0x2 << 0);			/* 使能写 */
	while (i<num) {
		EFR_ADR  = EEADR;			/* EFR_ADR寄存器写入EEADR地址 */
		EFR_DAT  = addr + i;		/* 写入目标地址,i为偏移量 */
		EFR_ADR  = EEDAT;			/* EFR_ADR寄存器写入EEDAT地址 */
		EFR_DAT  = *(dat + i);		/* 写入数据 */
		EFR_ADR  = EECTL;			/* EFR_ADR寄存器写入EECTL地址 */
		EFR_DAT |= (1 << 3);		/* 将WR置1，激活写周期 */
		while(EFR_DAT & (1 << 3));	/* 等待WR清0 */
		i++;
	}
	EFR_DAT &= ~(0x3 << 0);			/* 清0RWEN */
}

void data_flash_init(void)
{
	EFR_ADR  =  EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT &= ~(1	 << 7);			/* UDB控制器选择Data Flash */
	EFR_DAT &= ~(0x3 << 0);			/* 清0RWEN */
}

void led_init(void)
{
	P1MOD &= ~(1 << 0);				/* 配置P10为输出模式(LED0蓝) */
	P1DAT &= ~(1 << 0);				/* 配置P10初始输出低电平(灭) */
}

int main()
{
	unsigned char write_buffer[3] ={ 0x01, 0x02, 0x03 };
	unsigned char read_buffer[3]  ={ 0x04, 0x05, 0x06 };
	
	WDTCON  = 0x05;     							/* 关闭看门狗 */
	
	led_init();
	data_flash_init();
	
	data_flash_write(0x00, 3, &write_buffer);		/* 连续写入3个值至write_buffer */
	data_flash_read(0x00, 3, &read_buffer);			/* 连续读取3个值至read_buffer */

	while(1) {
		if (write_buffer[0] == read_buffer[0] &&	/* read_buffer与write_buffer相等时 */
			write_buffer[1] == read_buffer[1] &&
			write_buffer[2] == read_buffer[2]){
			P1DAT |= (1 << 0);      				/* 亮LED灯 */
		} else {
			P1DAT &= ~(1 << 0);      				/* 灭LED灯 */
		}
	}
}

