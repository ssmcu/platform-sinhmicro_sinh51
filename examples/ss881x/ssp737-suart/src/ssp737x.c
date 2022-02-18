/*
* ssp737x.c
* spp737x driver.
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

#include "ssp737x.h"
#include <SS881X.H>
#include "suart.h"

void delay_ms(unsigned short ms)
{
	unsigned short delay;
	while (ms--) {
		delay = 270;
		while (delay--);
	}
}

void ssp737_init(void)
{
    suart_init();
}

bit ssp737_write_reg(unsigned char reg, unsigned char val)
{
    unsigned char timout, retry_num;

    retry_num = 3;
    
    while (retry_num--) {
        suart_putc(SSP737_CMD_WR_REG);
        suart_putc(reg);
        suart_putc(val);

        timout = SSP737_RX_TIMOUT;            /* about 2ms@12M 4WC */
        while((!suart_receiver()) && (timout--));

        if (suart_getc() == SSP737_CMD_ACK) {
            return 1;
        }
    }

    return 0;
}

unsigned char ssp737_read_reg(ssp737_reg_t reg)
{
    unsigned char timout;

    suart_putc(SSP737_CMD_RD_REG);
    suart_putc(reg);

    timout = SSP737_RX_TIMOUT;
    while((!suart_receiver()) && (timout--));

    return suart_getc();
}

unsigned char ssp737_read_id(void)
{
    unsigned char timout;

    suart_putc(SSP737_CMD_ID_0);
    suart_putc(SSP737_CMD_ID_1);
    
    timout = SSP737_RX_TIMOUT;
    while((!suart_receiver()) && (timout--));
    
    return suart_getc();
}

void ssp737_ent_mcu_mode(void)
{
    SSP737_SET_TRX_IO(0);
    delay_ms(800);      /* not less than 800ms */
    SSP737_SET_TRX_IO(1);
    delay_ms(1);        /* 1ms waiting for work */
}

bit ssp737_exit_mcu_mode(void)
{
    unsigned char timout;

    suart_putc(SSP737_CMD_COMM_END_0);
    suart_putc(SSP737_CMD_COMM_END_1);

    timout = SSP737_RX_TIMOUT;
    while((!suart_receiver()) && (timout--));

    return (suart_getc() == SSP737_CMD_ACK);
}
