/*
 * timer2-hpwm.c
 *
 * HPWM test.
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
typedef unsigned long   uint32_t;
typedef unsigned short  uint16_t;
typedef unsigned char   uint8_t;
 
#define PWM_FREQ       (20000)      /* ����PWMƵ�� */
#define TIMER2_MAX_VAL  (8192)      /* ��ʱ��2�������� */
#define SCLK_FREQ       (12000000)  /* ʱ��Ƶ�ʣ��������Ϊ��SCLK/��Ƶϵ�� */
#define HPWM_MAX_DUTY    (pwm_max_duty() * 16)


void delay_ms(uint16_t ms)
{
				uint16_t delay;

				while (ms--) {
						delay = 270;
						while (delay--);
				}
}


void hpwm_init()
{
				CLKCON1 |= 0x10;     /* PFOUʱ��ʹ�� */
				DLLCON1 |= 0x10;     /* DDLƵ�ʷ�Χ4~12M Hz */
				DLLCON0 |= 0x03;     /* DDLʱ��ʹ�ܣ���ԴΪSCLK */
				HPWMCON0 |= 0x02;    /* �߾���PWM CC1ʹ�� */
}

 void pwm_set_freq(uint32_t freq)
 {
				uint16_t tr_val = TIMER2_MAX_VAL - SCLK_FREQ / freq;
				TRL2 = (tr_val & 0xFF);
				TRH2_0 = (TRH2_0 & 0x1F) | (((tr_val >> 8) & 0x7) << 5);
				TRH2_1 = (TRH2_1 & 0x9F) | (((tr_val >> 11) & 0x3) << 5);

 }

uint16_t pwm_max_duty(void)
{
 uint16_t tr_val = TRL2 | ((TRH2_0 & 0xE0) << 3) | ((TRH2_1 & 0x60) << 6);

    return (TIMER2_MAX_VAL - tr_val - 1);

}

void pwm_set_duty(uint16_t duty)
{
				uint16_t tcc_val = TIMER2_MAX_VAL - duty;  /* �Ƚ�ֵ */
				TCC1L = tcc_val & 0xff;
				TCC1H = (TCC1H & 0xE0) | ((tcc_val >> 8) & 0x1F);
}


void hpwm_set_duty(uint16_t duty)
{
				pwm_set_duty(duty / 16);
				HPWMCON0 = (HPWMCON0 & 0x0F) | ((duty % 16) << 4);
}

void pwm_enable_init()
{
				T2MOD = 0xFB; /* CC1�����ȽϹ��� */
				delay_ms(100);
				MFP1 = (MFP1 & 0xF3) | 0x04; /* P05��ΪCC1 */
}


 void main()
 {
				uint16_t duty = 0;

        WDTCON = 0x05;           /* �رտ��Ź� */
				CLKCON0 |= 0x01;         /* SCLKΪ��Ƶ12M Hz */
				CLKCON0 &= ~(0x7 << 1);  /* ��Ƶϵ��Ϊ 1 */
				T2CON &= 0x1F;           /* ��ʱ��2�ķ�Ƶϵ��Ϊ1 */
				TR2 = 1;                 /* ��ʱ��2���� */

				pwm_set_freq(PWM_FREQ);
				hpwm_init();
				hpwm_set_duty(duty);
	      pwm_enable_init();
				
				delay_ms(100);

				while (1) {
					duty++;
					if (duty >= HPWM_MAX_DUTY)
					duty = 0;

					hpwm_set_duty(duty);
					delay_ms(100);
					}
	 
 }