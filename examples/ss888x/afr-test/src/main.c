 /*
 * main.c
 *
 * afr-test.
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

static void delay_ms(unsigned int ms)
{	
    unsigned int i, j;
    do {
        i = 4;
        j = 200;
        do
        {
            while (--j);
        } while (--i);
    } while (--ms);
}


void main()
{
    WDTCON  = 0X05;                     /* 关看门狗 */
    P2_CTL2  = 0x08;              /* 将P23设为输入 */

	
    while (1) 
	{
         AFR_P2_PU	 |=  (0x1 << 3);           /* 将P23上拉使能 */
	     delay_ms(1000) ;
	     AFR_P2_PU	 &= ~(0x1 << 3);          /* 禁用P23上拉使能 */
		  delay_ms(1000) ;
    }
}
