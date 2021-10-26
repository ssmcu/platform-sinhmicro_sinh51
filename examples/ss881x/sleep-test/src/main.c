/*
 * sleep-test
 *
 * Sleep and wake up through wkup0 wake-up source.
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

void sleep_into()
{
    EFRADR = 0X10;                              /* 对EFR10H进行操作 */
    EFRDAT = 0X00;                              /* 不使能TS0唤醒 */
    DSEN   = 1;                                 /* 进入休眠 */
}


void main()
{
    WDTCON = 0X05;
    P0MOD  = 0X7f;                              /* P07作为输出，P01作输入 */
    P0PU   = 0X02;                              /* P01拉高 */ 
    while (1) {
        while (P0_1) {
            P0_7 = 1;
        }
        sleep_into();
    }
}
    
    
    

















