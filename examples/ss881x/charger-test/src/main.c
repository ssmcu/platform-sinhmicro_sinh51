/*
 * charger-test.c
 *
 * CHARGER test.
 *
 * Author: zhanyingwei<3080940495@qq.com>
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

short vbat_mv;
unsigned char num[5] ;

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

void uart_init()
{
	BRDSRC = 1;                          /* Using UART internal baud rate generator */
	BRPRE  = 1;                          /* prescaled to 13 */
	
	BR8  = 1;
	SBR  = 0xD0;                         /* bps = 19200 */
}

void adc_init()
{
    ADCCON0  &= ~0x40;                   /* continuity sampling */
    ADCCHEN  |= 0x01;                    /* enable VBAT channel */
}

void charger_init()
{
	CLKCON1  |= 0x08;                    /* send clock to charger */
	
	CHGCON0  |= 0xA0;                    /* set the constant current to 495mA, the timeout is 8 hours */
	CHGCON0  |= 0x01;                    /* enable charger */
	
	CHGCON1  |= 0xB8;                    /* set the constant voltage to 4.2V */
	
	CHGCON3  |= 0x0A;                    /* charging mode is normal mode */	
	
	CHGCON4  |= 0x01;                    /* enable intermittent constant voltage charging */
}

void vbat_read()
{
    vbat_mv  = ADCDAT0L + ((ADCDAT01H & 0x0F) << 8);
    vbat_mv  <<= 4;
    vbat_mv  >>= 4;
    vbat_mv  += 2600;
}

void num_handle()
{
	num[0]  = vbat_mv / 1000 % 10;
	num[1]  = vbat_mv / 100 % 10;
	num[2]  = vbat_mv / 10 % 10;
	num[3]  = vbat_mv % 10;
	num[4]  = '\0';
}

void HexToChar()
{
	num[0] = num[0] + 0x30;
	num[1] = num[1] + 0x30;
	num[2] = num[2] + 0x30;
	num[3] = num[3] + 0x30;
}

void uart_tx_8bits(unsigned char V_data)
{
	SBUF = V_data;
    while (!TI);
    TI   = 0;
}

void send_string(unsigned char *p){
	while (*p != '\0') {
		uart_tx_8bits(*p);
        p++;
	}
}

int main()
{
    WDTCON = 0x05;                       /* disable watchdog at startup */
	
	MFP1  |= 0x20;
	MFP2  |= 0x08;
	MFP3  |= 0x0A;                       /* P06 as UARTTX, P11 as UARTRX */
	
	charger_init();
	adc_init();
	uart_init();
       
    while (1) {
		vbat_read();
		num_handle();
		HexToChar();
		send_string("Vbat: ");
		send_string(num);
		send_string("mV");
		send_string("\n");
		_delay_ms(1000);
    }
}
