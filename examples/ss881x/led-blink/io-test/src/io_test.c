/*
 * io_test.c
 *
 * P06 and P07 read the status of P00 and P01 separately.
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

void init_port()
{
    /*
     * 将P00,P01,P06,P07设置为通用I/O
     */
	MFP0  &= ~0x0f;
	MFP1  &= ~0xf0;
    
	P0MOD |= 0x03;														
	P0PD  |= 0x03;			/* 给P00,P01下拉电阻变为低电平 */
	P0MOD &= ~0xc0;				
}

/*
 * 函数功能：在P06和P07上输出P00和P01的状态
 */
void io_contact()								
{
	if (P0_0) {
		P0_6 = 1;
	} else {
		P0_6 = 0;
	}
		
	if (P0_1) {
		P0_7 = 1;
	} else {
		P0_7 = 0;
	}
}
	
void main()
{
    WDTCON = 0x05;          /* 关闭看门狗 */
	init_port();
	while (1) {
		io_contact();
	}
}
