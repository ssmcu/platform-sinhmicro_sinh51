 /*
 * main.c
 *
 * sleep-ram-test.
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

/* xdata通常方式的读取函数，地址范围为8000H~82C0H(设置的xdata地址) */
void xdata_normal_read(unsigned char xdata *p, unsigned char num, unsigned char *dat)
{
	while( num ) {
		*dat = *p;
		p++;
		dat++;
		num--;
	}
}

/* xdata通常方式的写入函数，地址范围为8000H~82C0H(设置的xdata地址) */
void xdata_normal_write(unsigned char xdata *p, unsigned char num, unsigned char *dat)
{
	while( num ) {
		*p = *dat;
		p++;
		dat++;
		num--;
	}
}

/* xdata断电保持方式的读取函数，地址范围为00H~7FH，映射xdata的82C0H~833FH */
void xdata_keep_read(unsigned char addr, unsigned char num, unsigned char *dat)
{
	unsigned char i = 0;
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT |= (0x1 << 0);			/* 使能读 */
	while(i < num){
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

/* xdata断电保持方式的函数，地址范围为00H~7FH，映射xdata的82C0H~833FH */
void xdata_keep_write(unsigned char addr, unsigned char num, unsigned char *dat)
{
	unsigned char i = 0;
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT |= (0x2 << 0);			/* 使能写 */
	while (i < num) {
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

void xdata_keep_init(void)
{
	EFR_ADR  = EECTL;				/* EFR_ADR寄存器写入EECTL地址 */
	EFR_DAT &= ~(1	 << 7);			/* UDB控制器选择XDATA */
	EFR_DAT &= ~(0x3 << 0);			/* 清0RWEN */
}

void led_init(void)
{
	P0MOD &= ~(1 << 7);				/* 配置P07为输出模式(LED0绿) */
	P0DAT &= ~(1 << 7);				/* 配置P07初始输出低电平(灭) */
	P1MOD &= ~(1 << 0);				/* 配置P10为输出模式(LED1蓝) */
	P1DAT &= ~(1 << 0);				/* 配置P10初始输出低电平(灭) */
	EFR_ADR  = TKGPIO0;
	EFR_DAT &= ~((1 << 4) | (1 << 0));/* 配置P15推挽输出输出、默认低电平(LED2红灭) */
}

void sleep_init(void)
{
	AFR_IOWK1_CTL = 0x00;			/* 其他唤醒源不唤醒 */
	P0MOD |= (1 << 6);				/* 开启P04SLPWK0唤醒源 */
}

unsigned char sleep_scan(void)
{
	EFR_ADR  = RESETS1;				/* EFR_ADR寄存器写入RESETS1地址 */
	if(!(EFR_DAT & (1 << 7))){		/* 检测RESETS1寄存器的FON位 */
		return 1;
	} else {
		return 0;
	}
}

void enter_sleep(void)
{
	EFR_ADR  = RESETS1;				/* EFR_ADR寄存器写入RESETS1地址 */
	EFR_DAT &= ~(1 << 7);			/* RESETS1寄存器的FON位清0 */
	DSEN 	 = 1;					/* 置位进入休眠 */
}

static void delay_ms(unsigned short ms)
{	
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do {
            while (--j);
        } while (--i);
    } while (--ms);
}

int main()
{
	unsigned char write_buffer[2]	= { 0x01, 0x02 };				
	unsigned char 	keep_read_buffer[2]  	= { 0 },
					normal_read_buffer[2] 	= { 0 };
					
	WDTCON = 0x05;     										/* 关闭看门狗 */
	
	sleep_init();
	led_init();
	xdata_keep_init();

	if (sleep_scan() ) {									/* 从休眠模式唤醒复位 */
		xdata_normal_read(0x8000, 2, &normal_read_buffer);	/* 通常方式读取xdata值 */
		xdata_keep_read(0x70, 2, &keep_read_buffer);		/* 断电保持方式读取xdata值(必须为UDB方式读取) */
	} else {												/* 正常上电 */
		P0DAT |= (1 << 7);									/* 亮LED0绿灯 */
		delay_ms(2000);										/* 约2秒 */
		
		xdata_normal_write(0x8000, 2, &write_buffer);		/* 通常方式写入xdata值 */
		xdata_keep_write(0x70, 2, &write_buffer);			/* 断电保持方式写入xdata值(可为UDB方式写入) */
		
		enter_sleep();										/* 进入休眠 */
	}
	
	while (1) {
		if (write_buffer[0] == normal_read_buffer[0] &&		/* xdata通常方式的判断 */
			write_buffer[1] == normal_read_buffer[1] ) {
			EFR_ADR  = TKGPIO0;
			EFR_DAT |= (1 << 0);  							/* 一致则亮LED2红灯 */
		} else {
			EFR_ADR  = TKGPIO0;
			EFR_DAT &= ~(1 << 0);  							/* 否则灭LED2红灯 */
		}
		
		if (write_buffer[0] == keep_read_buffer[0] &&		/* xdata断电保持方式的判断 */
			write_buffer[1] == keep_read_buffer[1] ) {
			P1DAT |= (1 << 0);   							/* 一致则亮LED1蓝灯 */
		} else {
			P1DAT &= ~(1 << 0);   							/* 否则灭LED1蓝灯 */
		}
			
		delay_ms(200);	
	}
}

