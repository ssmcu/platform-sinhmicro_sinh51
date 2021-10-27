/*
 * hardware breathLED
 *
 * Use the hardware breathLED mode output.
 *
 * Author: <liwanbang@sinhmicro.com.cn>
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

void breath_init(void)
{
        MFP0  = 0x01;           /* P00 work in pwm0 */
	
        TBLNCON0 &= ~0xf0;      /* set on 4s */

        TCON  |=0x07;           /* start timer0,PWMx,BLNx */
 
}

void main()
{    
        WDTCON = 0x05;                           /* stop watch dog*/
        
        breath_init();
    
        while (1){
			
        }
}
