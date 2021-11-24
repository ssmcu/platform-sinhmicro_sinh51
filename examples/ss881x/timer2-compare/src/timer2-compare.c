/*
 * timer2-compare.c
 *
 * PWM test.
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
typedef unsigned short  uint16_t;
typedef unsigned char   uint8_t;

#define slk_div                (1)     /* 分频系数 */
#define freq                   (4000) /* 设置spwm的频率 */
#define timer2_max_val         (8192)  /* 定时器2最大计数值 */
#define spwm_max_duty          (12000000 / freq / slk_div)
#define timer2_reload_val      (timer2_max_val - (12000000/freq /slk_div)) 

/* 配置使能的spwm I/O口 */
#define CONFIG_SMPWM_IO_0           (0x02)
#define CONFIG_SMPWM_IO_1           (0x05)
#define CONFIG_SMPWM_IO_2           (0x06)
#define CONFIG_SMPWM_IO_3           (0x07)


/* 设置spwm的占空比  0~spwm_max_duty(3000)  */
#define   duty_0    (1000)     /* CC0的占空比 */
#define   duty_1    (1500)     /* CC1的占空比 */
#define   duty_2    (2000)     /* CC2的占空比 */
#define   duty_3    (2500)     /* CC3的占空比 */

enum smart_pwm_id {
        SMPWM0 = 0,
        SMPWM1,
        SMPWM2,
        SMPWM3,
};


static uint16_t spwm_duty2tcc(uint16_t duty)
{
      uint16_t tcc_val = timer2_max_val;

      if (duty == 0) {
          return timer2_max_val - 1;
      } 
      else if (duty == spwm_max_duty) {
          return timer2_reload_val;
      } else {
               while (duty--)
               tcc_val -=(12000000 / freq / slk_div / spwm_max_duty);
               return tcc_val;
      }
}


void delay_ms(uint16_t ms)
{
      uint16_t delay;
      while (ms--) {
             delay = 270;
             while (delay--);
      }
}


void spwm_int()
{
      CLKCON0 |= 0x01;      /* SLK为12MHz */
      T2CON   |= 0x00;      /*分频系数为1 */
      TR2 = 1;
}



static void smpwm_io_enable(uint8_t smpwm)
{
      switch (smpwm){

       case SMPWM0:
                #if (CONFIG_SMPWM_IO_0 == 0x02)
                     MFP0 = (MFP0 & 0xCF) | 0x30;
                #elif (CONFIG_SMPWM_IO_0 == 0x04)
                     MFP1 = (MFP1 & 0xFC) | 0x01;
                #endif
                break;

       case SMPWM1:
                #if (CONFIG_SMPWM_IO_1 == 0x05)
                     MFP1 = (MFP1 & 0xF3) | 0x04;
                #elif (CONFIG_SMPWM_IO_1 == 0x10)
                     MFP2 = (MFP2 & 0xFC) | 0x03;
                #endif
                break;

       case SMPWM2:
                #if (CONFIG_SMPWM_IO_2 == 0x06)
                     MFP1 = (MFP1 & 0xCF) | 0x10;
                #elif (CONFIG_SMPWM_IO_2 == 0x14)
                     MFP3 = (MFP3 & 0xCF) | 0x20;
                #elif (CONFIG_SMPWM_IO_2 == 0x15)
			       /* set p15 as cc2 */
                     efr_bit_change(EXTMFP0, 6, 3, SET);
                #endif
                break;

     case SMPWM3:
                #if (CONFIG_SMPWM_IO_3 == 0x07)
                     MFP1 = (MFP1 & 0x3F) | 0x40;
                #endif
                break;

                default:
                break;
      }
}


void spwm_set_freq(uint16_t pwm_freq)
{
     uint16_t tr_val =  (timer2_max_val - 12000000/ pwm_freq / slk_div);   /* 计算重载值 */
     TRL2   = (tr_val  & 0xFF);
     TRH2_0 = (TRH2_0 & 0x1F) | (((tr_val >> 8) & 0x7) << 5);
     TRH2_1 = (TRH2_1 & 0x9F) | (((tr_val >> 11) & 0x3) << 5);            /* 将重载填入寄存器 */
}


void spwm_set_duty(uint8_t smpwm, uint16_t duty)
{
  uint16_t tcc_val = spwm_duty2tcc(duty);

      switch (smpwm) {

       case 0:
           TCC0L = tcc_val & 0x16;
           TCC0H = (TCC0H & 0xE0) | ((tcc_val >> 8) & 0x1F);
           break;

       case 1:
           TCC1L = tcc_val & 0xff;
           TCC1H = (TCC1H & 0xE0) | ((tcc_val >> 8) & 0x1F);
           break;

       case 2:
           TCC2L = tcc_val & 0xff;
           TCC2H = (TCC2H & 0xE0) | ((tcc_val >> 8) & 0x1F);
           break;

       case 3:
           TCC3L = tcc_val & 0xff;
           TCC3H = (TCC3H & 0xE0) | ((tcc_val >> 8) & 0x1F);
           break;
           default:
           break;
      }
}

void spwm_enable(uint8_t smpwm)
{
      T2MOD = (T2MOD & ~(0x3 << (smpwm << 1))) | (0x2 << (smpwm << 1));
      delay_ms(10);
      smpwm_io_enable(smpwm);
}




void main()
{
      WDTCON = 0x05 ;        /* 关闭看门狗 */

      spwm_int();             

      spwm_set_freq(freq);   /* spwm 设置固定频率 */


      /* spwm set duty */
      spwm_set_duty(0, (duty_0));
      spwm_set_duty(1, (duty_1));
      spwm_set_duty(2, (duty_2));
      spwm_set_duty(3, (duty_3));


      while (1) {
      /* spwm enable */
      spwm_enable(0);
      spwm_enable(1);
      spwm_enable(2);
      spwm_enable(3);
      }
}





