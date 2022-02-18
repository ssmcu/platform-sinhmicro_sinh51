/*
* ssp737x.h
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
#ifndef __SSP737X_H__
#define __SSP737X_H__
#include "suart.h"

#define SSP737_SET_TRX_IO(io_sta)    do {SUART_SET_TRX_PIN(io_sta); SUART_SET_TX();} while(0)   /* set to gpio output with 'io_sta' level*/

#define SSP737_RX_TIMOUT             (255)

/* SSP737 communication command */
#define SSP737_ID                    (0x41)
#define SSP737_CMD_ID_0              (0xF8)
#define SSP737_CMD_ID_1              (0x0D)
#define SSP737_CMD_RD_REG            (0xF5)
#define SSP737_CMD_WR_REG            (0xFA)
#define SSP737_CMD_COMM_END_0        (0xF8)
#define SSP737_CMD_COMM_END_1        (0xF2)
#define SSP737_CMD_ACK               (0x5A)
#define SSP737_CMD_NACK              (0xA5)

/* SSP737 register */
typedef enum {
    SSP737_REG_BAUD        = 0x11,
    SSP737_REG_MODE_CTL    = 0x31,
    SSP737_REG_WKUP_CTL    = 0x32,
    SSP737_REG_RESETS      = 0x34,
    SSP737_REG_BST_CTL     = 0x23,
    SSP737_REG_CHG_CTL0    = 0x20,
    SSP737_REG_CHG_CTL1    = 0x21,
    SSP737_REG_CHG_STA     = 0x22,
    SSP737_REG_POART_DAT   = 0x50,
    SSP737_REG_PORT_OE_IE  = 0x51,
    SSP737_REG_PORT_PU_PD  = 0x52,
    SSP737_REG_PORT_MFP    = 0x54,
    SSP737_REG_LK_CTL0     = 0x40,
    SSP737_REG_LK_CTL1     = 0x41,
    SSP737_REG_LK_CTL2     = 0x42,
    SSP737_REG_PWM_CLK_CTL = 0x33,
} ssp737_reg_t;

typedef enum {
    BST_EN     = 0x01,
    BST_EN_MSK = 0x01,

    BST_OV_4V5   = 0x00,  /* BOOST output voltage 4.5V */
    BST_OV_5V    = 0x10,
    BST_OV_5V5   = 0x20,
    BST_OV_6V    = 0x30,
    BST_OV_MSK   = 0xF0
} BST_CTL;

void ssp737_init(void);
bit ssp737_write_reg(unsigned char reg, unsigned char val);
unsigned char ssp737_read_reg(ssp737_reg_t reg);
unsigned char ssp737_read_id(void);
void ssp737_ent_mcu_mode(void);
bit ssp737_exit_mcu_mode(void);

#endif
