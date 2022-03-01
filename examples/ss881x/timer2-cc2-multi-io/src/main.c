/*
 * main.c
 *
 * timer2-cc2-multi-test.
 *
 * Author: lizanyu<lizanyu@sinhmicro.com>
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

#include "ss881x.h"
typedef unsigned short  uint16_t;
typedef unsigned char   uint8_t;

#define slk_div                (1)     /* 分频系数 */
#define freq                   (4000) /* 设置spwm的频率 */
#define timer2_max_val         (8192)  /* 定时器2最大计数值 */
#define spwm_max_duty          (12000000 / freq / slk_div)
#define timer2_reload_val      (timer2_max_val - (12000000/freq /slk_div)) 


/* 设置spwm的占空比  0~spwm_max_duty(3000)  */
#define   duty_2    (2000)     /* CC2的占空比 */


void delay_ms(uint16_t ms)
{
      uint16_t delay;
      while (ms--) 
      {
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


void spwm_enable()
{
      T2MOD = 0x20 ;
      delay_ms(10);
/* 复用P06,P14,P15为CC2口 */
      MFP1 = 0x10 ;
      MFP3 = 0x20 ;
      EFRADR = 0x12 ;
      EFRDAT = 0xC0 ;

}


void spwm_set_freq(uint16_t pwm_freq)
{
     uint16_t tr_val =  (timer2_max_val - 12000000/ pwm_freq / slk_div);   /* 计算寄存器装载值 */
     TRL2   = (tr_val  & 0xFF);
     TRH2_0 = (TRH2_0 & 0x1F) | (((tr_val >> 8) & 0x7) << 5);
     TRH2_1 = (TRH2_1 & 0x9F) | (((tr_val >> 11) & 0x3) << 5);            /* 将重载填入寄存器 */
}


static uint16_t spwm_duty2tcc(uint16_t duty)              /* PWM占空比设置 */
{
      uint16_t tcc_val = timer2_max_val;
      while (duty--)
      tcc_val -- ;	           
      return tcc_val;

}


void spwm_set_duty(uint16_t duty)
{
      uint16_t tcc_val = spwm_duty2tcc(duty);
      TCC2L = tcc_val & 0xff;
      TCC2H = (TCC2H & 0xE0) | ((tcc_val >> 8) & 0x1F);
}


void main()
{
      WDTCON = 0x05 ;          /* 关闭看门狗 */
      spwm_int();  
      spwm_enable();  		 /* spwm enable */
      spwm_set_freq(freq);     /* spwm 设置固定频率 */
      spwm_set_duty(duty_2);   /* spwm set duty */

      while (1) 
      {
            
      }
}





