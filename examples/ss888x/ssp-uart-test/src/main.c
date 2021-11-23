/* Author: zhanyingwei<3080940495@qq.com>
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

static void _delay_ms(unsigned char ms)
{	
    unsigned char i, j;
    do {
        i = 4;
        j = 200;
        do
        {
            while (--j);
        } while (--i);
    } while (--ms);
}

void ssp_uart_init()
{
	CLK_CTL2  |= 0x08;
	
	AFR_SSP_CON0  = 0x35;                      /* PWM 编码*/
	
	AFR_SSP_T_START = 0x01;
	AFR_SSP_T_ZERO  = 0x01;
	AFR_SSP_T_ONE   = 0x10;
	AFR_SSP_T_STOP  = 0x10;
}

void ssp_uart_tx(unsigned char dt)
{
	while ((AFR_SSP_FIFOSTART & 0x01) != 0);
	AFR_SSP_DAT  = dt;
}

int main()
{
	WDTCON = 0x05;                             /* disable watchdog at startup */
	
	MFP3  |= 0x10;                             /* P14 as ssp */
	
	ssp_uart_init();
	
	while (1) {
		ssp_uart_tx(0xAA);
		_delay_ms(500);
		ssp_uart_tx(0x55);
		_delay_ms(500);
	}
}
