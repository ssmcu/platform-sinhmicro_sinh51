/*
 * efr_io_test.c
 *
 * efr test.
 *
 * Author: chenjingfan<chenjingfan@sinhmicro.com>
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
#include "efr.h"
#define EXTMFP0     (0x12)
#define PEXTCON0    (0x14)  


int main()
{
        EFR_ADDR = EXTMFP0 ;        /* 将EFR寄存器地址写入EFRADR */
        EFR_DAT &= ~(0x03 << 6) ;   /* P15作为GPIO口 */
        EFR_ADDR = PEXTCON0;       
        EFR_DAT  = (0x61) ;         /* 通过EFRADC读写P15输出高电平1 */
        while (1) {
        }
}







