/*
* main.c
* Enable or disable SSP737x boost.
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
#include "ssp737x.h"

void main(void)
{
    unsigned char key_deb;
    bit boost_en, ssp737_ok;
	
	WDTCON = 0x05;
    P1PUPD |= 0x02;
    
    ssp737_init();
    ssp737_ent_mcu_mode();
    ssp737_ok = ssp737_read_id() == SSP737_ID;
	
    while(1) {
		if (P1_1) {
			if (key_deb < 200) {
				key_deb++;
			}
		} else {
			key_deb = 0;
		}

		if (key_deb == 200) {
			key_deb = 201;
			boost_en = !boost_en;
			if (boost_en) {
				ssp737_write_reg(SSP737_REG_BST_CTL, BST_EN | BST_OV_5V);
			} else {
				ssp737_write_reg(SSP737_REG_BST_CTL, 0);
			}
		}
    }
}
