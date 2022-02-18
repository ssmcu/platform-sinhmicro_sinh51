/*
* suart.c
* IO simulate half-duplex uart.
* default configuration:
*	1bit start, 8bit data, 1bit stop, 1bit check bit(odd)
*	baud rate 10kbps@SS881X, 12MHz, wait cycle 4
*
* Copyright (C) 2021 Sinh Micro, Inc.
* Author: zhangzhao@sinhmicro.com.cn
*
* Changelog:
* 20220214: Init version
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
#include <SS881X.H>
#include "suart.h"

bit suart_rx_cplt;
unsigned char suart_rx_dat;
unsigned char bdata suart_trx_dat;
sbit suart_trx_dat_b0 = suart_trx_dat^0;
sbit suart_trx_dat_b1 = suart_trx_dat^1;
sbit suart_trx_dat_b2 = suart_trx_dat^2;
sbit suart_trx_dat_b3 = suart_trx_dat^3;
sbit suart_trx_dat_b4 = suart_trx_dat^4;
sbit suart_trx_dat_b5 = suart_trx_dat^5;
sbit suart_trx_dat_b6 = suart_trx_dat^6;
sbit suart_trx_dat_b7 = suart_trx_dat^7;

#if (SUART_CONFIGURABLE_BR == 1)
unsigned char whole_bit_tim, half_bit_tim;
#endif

static bit suart_calc_check(unsigned char dat);

void suart_delay(unsigned char dly)
{
    while(dly--);
}

void suart_init(void)
{
    /* set P0_1 as GPIO and output high */
    MFP0 &= 0xF3;
    P0_1 = 1;
    P0PU |= 0x02;
    SUART_SET_TX();
}

static bit suart_calc_check(unsigned char dat)
{
#if (SUART_PARITY_CHCEK == SUART_PARITY_CHCEK_ODD)
    unsigned char idx;
    unsigned char  verify_bit;
    
    verify_bit = 1;
    idx = 8;

    while(idx--) {
        verify_bit ^= dat;
		dat >>= 1;
    }
	
	verify_bit &= 0x01;
	
    return verify_bit;
#else
    #error([suart] This verification method is not supported!)
#endif
}

void suart_putc(unsigned char c)
{
    bit verify_bit;

    suart_trx_dat = c;
    verify_bit = suart_calc_check(suart_trx_dat);

    SUART_SET_TX();

    SUART_IRQ_DISABLE();

    SUART_SET_TRX_PIN(0);
    SUART_BIT_TIME_WHOLE();

    SUART_SET_TRX_PIN(suart_trx_dat_b0);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b1);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b2);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b3);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b4);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b5);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b6);
    SUART_BIT_TIME_WHOLE();
    SUART_SET_TRX_PIN(suart_trx_dat_b7);
    SUART_BIT_TIME_WHOLE();

    SUART_SET_TRX_PIN(verify_bit);
    SUART_BIT_TIME_WHOLE();

    SUART_SET_TRX_PIN(1);
    SUART_BIT_TIME_WHOLE();

    SUART_IRQ_ENABLE();

#if (SUART_SEND_CLR_RX_DATA == 1)
    suart_rx_dat = 0;
    suart_rx_cplt = 0;
#endif
}

unsigned char suart_getc(void)
{
    suart_rx_cplt = 0;

    return suart_rx_dat;
}

bit suart_receiver(void)
{
    bit start_bit, stop_bit, verify_bit;

    SUART_SET_RX();
	
    SUART_IRQ_DISABLE();

	if (!SUART_GET_TRX_PIN()) {
		suart_trx_dat = 0;
        SUART_BIT_TIME_HALF();
        start_bit = SUART_GET_TRX_PIN();

        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b0 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b1 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b2 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b3 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b4 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b5 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b6 = SUART_GET_TRX_PIN();
        SUART_BIT_TIME_WHOLE();
        suart_trx_dat_b7 = SUART_GET_TRX_PIN();

#if (SUART_PARITY_CHCEK !=  SUART_PARITY_CHCEK_NONE)
        SUART_BIT_TIME_WHOLE();
        verify_bit = SUART_GET_TRX_PIN();
#endif

        SUART_BIT_TIME_WHOLE();
        stop_bit = SUART_GET_TRX_PIN();
		
		SUART_BIT_TIME_HALF();

        suart_rx_cplt = 0;
#if (SUART_PARITY_CHCEK !=  SUART_PARITY_CHCEK_NONE)
        if ((!start_bit) && stop_bit && \
            (verify_bit == suart_calc_check(suart_trx_dat))) {
#else
        if ((!start_bit) && stop_bit) {
#endif
            suart_rx_cplt = 1;
			suart_rx_dat  = suart_trx_dat;
        }
	}

    SUART_IRQ_ENABLE();

    return suart_rx_cplt;
}

#if (SUART_CONFIGURABLE_BR == 1)
void suart_set_baudrate(unsigned char whole, unsigned char half)
{
    whole_bit_tim = whole;
    half_bit_tim  = half;
}
#endif
