/*
 * main.c
 *
 * io-cc-test.
 *
 * Author: lizanyu<lizanyu@sinhmicro.com.cn>
 * 
 * Copyright (C) 2022 Sinh Micro, Inc.
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

void init_port()
{
    EFR_ADDR = LDO_CTL ;        /* 将EFR寄存器地址写入EFRADR */
    EFR_DAT = 0x30 ;             /* BGREN,IBIASEN使能*/
	         
	  P2_CTL2 &= ~ (0x1 << 3);         /* 将P23设为输出*/
	
	  AFR_IO_OM_CTL1  = 0xE2 ;         /* 输出模式设为恒流输出，6mA*/

}

void main()
{
    WDTCON  = 0X05;                     /* 关看门狗 */
    init_port();
	
    while (1){
    }
}