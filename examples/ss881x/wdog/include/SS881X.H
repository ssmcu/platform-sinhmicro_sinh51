/*
 * SS881X.H
 *
 * Header file for Sinh Micro SS881X microcontroller.
 * 
 * Author: lipeng<lp@sinhmicro.com>
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

#ifndef __REG_SS881X_H__
#define __REG_SS881X_H__

#if defined(__C51__)    /* keil C51 */
/*
 * BYTE Register
 */

/* MCU Core */
sfr SP          = 0x81;
sfr DPL         = 0x82; 
sfr DPH         = 0x83;  
sfr DPL1        = 0x84; 
sfr DPH1        = 0x85;
sfr DPSEL       = 0x92; 
sfr PSW         = 0xD0; 
sfr ACC         = 0xE0; 
sfr B           = 0xF0; 

/* Power */
sfr PCON        = 0x87; 
sfr PWRCON0     = 0xF8;
sfr PWRCON1     = 0xF9;
sfr PWRCON2     = 0xFB;
sfr PWRCON3     = 0xFC;
sfr PWRCON4     = 0xFE;
sfr PWRSTAT     = 0xFD;

/* Clock */
sfr CKCON       = 0x8E; 
sfr RCCON       = 0xA6;
sfr CLKCON0     = 0xB0;
sfr CLKCON1     = 0xB1;

/* Reset */
sfr RESETS      = 0xA0;

/* watchdog */
sfr WDTCON      = 0x86;

/* Charger */
sfr CHGCON0     = 0xB6;
sfr CHGCON1     = 0xB2;
sfr CHGCON2     = 0xB3;
sfr CHGCON3     = 0xB5;
sfr CHGCON4     = 0x9F;
sfr CHGCON5     = 0xB4;
sfr CHGSTAT     = 0xB7;
sfr BATSTAT     = 0xFF;

/* I/O port */
sfr P0DAT       = 0x80;
sfr P0          = 0x80; // Dummy name
sfr P0MOD       = 0x95;
sfr P0PU        = 0x96;
sfr P0PD        = 0x97;
sfr P1DAT       = 0x90;
sfr P1          = 0x90;
sfr P1MOD       = 0x91;
sfr P1OM        = 0x93;
sfr P1PUPD      = 0x94;
sfr PWKCTL      = 0xA7;
sfr PDRV0       = 0xAA;
sfr PDRV1       = 0xAF;
sfr MFP0        = 0xAB;
sfr MFP1        = 0xAC;
sfr MFP2        = 0xAD;
sfr MFP3        = 0xAE;


/* Interrupt */
sfr INTCON0     = 0xA8;
sfr INTCON1     = 0xB8;
sfr INTCON2     = 0xC0;
sfr INTEN0      = 0xA8;
sfr INTEN1      = 0xB8;
sfr INTEN2      = 0xC0;
sfr EINTCON     = 0xA9;
sfr INTPRIO     = 0xB9;


/* Timer */
sfr TCON        = 0x88;
sfr TCON1       = 0xA1;
sfr TMOD        = 0x89;
sfr TL0         = 0x8A;
sfr TL1         = 0x8B;
sfr TH0         = 0x8C;
sfr TH1	        = 0x8D;
sfr TPDL0       = 0xA2;
sfr TBLNCON0    = 0xA2; // TPDL0/TBLNCON0
sfr TPDH0       = 0xA3;
sfr TPDL1       = 0xA4;
sfr TBLNCON1    = 0xA4; // TPDL1/TBLNCON1
sfr TPDH1       = 0xA5;

sfr T2CON       = 0xC8;
sfr T2MOD       = 0xC1;
sfr T2STAT      = 0xC9;
sfr T2D0        = 0xC2;
sfr TL2	        = 0xC2; // dummy name
sfr T2D1        = 0xC3;
sfr TRL2        = 0xC3; // dummy name
sfr T2D2        = 0xC4;
sfr TCC0L       = 0xC4; // dummy name
sfr T2D3        = 0xC5;
sfr TCC1L       = 0xC5; // dummy name
sfr T2D4        = 0xC6;
sfr TCC2L       = 0xC6; // dummy name
sfr T2D5        = 0xC7;
sfr TCC3L       = 0xC7; // dummy name
sfr T2D6        = 0xCA;
sfr TCC0H       = 0xCA; // dummy name
sfr TH2_0       = 0xCA; // dummy name
sfr T2D7        = 0xCB;
sfr TCC1H       = 0xCB; // dummy name
sfr TRH2_0      = 0xCB; // dummy name
sfr T2D8        = 0xCC;
sfr TCC2H       = 0xCC; // dummy name
sfr TH2_1       = 0xCC; // dummy name
sfr T2D9        = 0xCD;
sfr TCC3H       = 0xCD; // dummy name
sfr TRH2_1      = 0xCD; // dummy name

/* LCD */
sfr LCDCON      = 0xD7;

/* Serial */
sfr SCON        = 0x98;
sfr SBUF        = 0x99;
sfr SBR         = 0x9A;

/* I2C */
sfr IICCON      = 0xD1;
sfr IICSTAT     = 0xD2;
sfr IICADDR     = 0xD3;
sfr IICDAT      = 0xD4;
sfr IICDIV      = 0xD5;

/* SDP */
sfr SDPCON0     = 0xD8;
sfr SDPCON1     = 0xDF;
sfr SDPNM       = 0xD9;
sfr SDPDA       = 0xDA;
sfr SDPDAT0     = 0xDB;
sfr SDPDAT1     = 0xDC;
sfr SDPDAT2     = 0xDD;
sfr SDPDAT3     = 0xDE;

/* ADC */
sfr ADCCON0     = 0xE6;
sfr ADCCON1     = 0xE7;
sfr ADCCON2     = 0xF5;
sfr ADCCON3     = 0xF7;

sfr ADCCHEN     = 0xE8;
sfr ADCDAT0L    = 0xE1;
sfr ADCDAT1L    = 0xE9;
sfr ADCDAT01H   = 0xEA;
sfr ADCDAT2L    = 0xEB;
sfr ADCDAT3L    = 0xEC;
sfr ADCDAT23H   = 0xED;
sfr ADCDAT4L    = 0xEE;
sfr ADCDAT5L    = 0xEF;
sfr ADCDAT45H   = 0xF1;
sfr ADCDAT6L    = 0xF2;
sfr ADCDAT7L    = 0xF3;
sfr ADCDAT67H   = 0xF4;

sfr DCMPCON0    = 0xBD;
sfr DCMPCON1    = 0xBE;
sfr DCMPNDATL   = 0xBF;


/* CMP */
sfr CMPCON0     = 0xBA;
sfr CMPCON1     = 0xBB;
sfr CMPCON2     = 0xBC;

/* PFOU */
sfr PRCCON0     = 0xE2;
sfr PRCCON1     = 0xE3;
sfr PRCCON2     = 0xD6;
sfr PRCFREQL    = 0xE4;
sfr DLLCON0     = 0xE5;
sfr DLLCON1     = 0xCF;
sfr HPWMCON0    = 0x9B;
sfr HPWMDZT0    = 0x9C;
sfr HPWMDZT1    = 0x9D;

sfr EFRADR      = 0x84;
sfr EFRDAT      = 0x85;

sfr TICKCON     = 0x8F;

/*
 * BIT Register
 */

/*  PSW   */
sbit CY         = 0xD7; 
sbit AC         = 0xD6; 
sbit F0         = 0xD5; 
sbit RS1        = 0xD4; 
sbit RS0        = 0xD3; 
sbit OV         = 0xD2; 
sbit P          = 0xD0; 

/* PWR_CTL0 */
sbit VKEYEN     = 0xFC;
sbit PCHGEN     = 0xFB;

/* CLKCON0 */
sbit DSEN       = 0xB7;
sbit WDTWKEN    = 0xB6;
sbit SCLKSRC    = 0xB0;

/* RESETS */
sbit WDTCLR     = 0xA7;
sbit SSDF       = 0xA5;
sbit WDOF       = 0xA4;
sbit LVRF       = 0xA3;
sbit ABNF       = 0xA2;
sbit PINF       = 0xA1;
sbit PORF       = 0xA0;

/* P0 */
sbit P0_7       = 0x87;
sbit P0_6       = 0x86;
sbit P0_5       = 0x85;
sbit P0_4       = 0x84;
sbit P0_3       = 0x83;
sbit P0_2       = 0x82;
sbit P0_1       = 0x81;
sbit P0_0       = 0x80;

/* P1 */
sbit P06WKF     = 0x97;
sbit P04WKF     = 0x96;
sbit P03WKF     = 0x95;
sbit P1_4       = 0x94;
sbit P1_3       = 0x93;
sbit P1_2       = 0x92;
sbit P1_1       = 0x91;
sbit P1_0       = 0x90;

/* INTCON0 */
sbit EA         = 0xAF; 
sbit ECHG       = 0xAE;
sbit ECMP       = 0xAD;
sbit ELV        = 0xAB;
sbit EOT        = 0xAA;
sbit EIIC       = 0xA9;
sbit EUART      = 0xA8;

/* INTCON1 */
sbit ESDP       = 0xBF; 
sbit ET0        = 0xBE; 
sbit ET1        = 0xBD; 
sbit ET2        = 0xBC; 
sbit ET2C3      = 0xBB; 
sbit ET2C2      = 0xBA;
sbit ET2C1      = 0xB9;
sbit ET2C0      = 0xB8;

/* INTCON2 */
sbit ETICK      = 0xC5;
sbit EOC        = 0xC4;
sbit EOV        = 0xC3;
sbit EADC       = 0xC2;
sbit EX1        = 0xC1;
sbit EX0        = 0xC0;

/*  TCON  */
sbit TF1        = 0x8F; 
sbit TR1        = 0x8E;
sbit TPE1       = 0x8D;
sbit TBLNE1     = 0x8C;
sbit TF0        = 0x8B;
sbit TR0        = 0x8A;
sbit TPE0       = 0x89;
sbit TBLNE0     = 0x88; 

/*  T2CON  */
sbit TR2        = 0xCC;
sbit TCCS3      = 0xCB;
sbit TCCS2      = 0xCA;
sbit TCCS1      = 0xC9;
sbit TCCS0      = 0xC8; 

/* SCON */
sbit PAREN      = 0x9F;
sbit BRDSRC     = 0x9E;
sbit BR8        = 0x9D;
sbit REN        = 0x9C;
sbit RER        = 0x9B;
sbit BRPRE      = 0x9A;
sbit TI         = 0x99;
sbit RI         = 0x98;

/* SDPCON0 */
sbit SDPERR     = 0xDF;
sbit SDPIF      = 0xDE;
sbit SDPCHECK   = 0xDF;
sbit DMODE      = 0xDC;
sbit MSTART     = 0xDB;

/* ADCCHEN */
sbit VBATEN     = 0xEF;
sbit IBATEN     = 0xEE;
sbit AN5EN      = 0xED;
sbit AN4EN      = 0xEC;
sbit AN3EN      = 0xEB;
sbit AN2EN      = 0xEA;
sbit AN1EN      = 0xE9;
sbit AN0EN      = 0xE8;

#elif defined(__SDCC)    /* SDCC */
/*
 * BYTE Register
 */

/* MCU Core */
__sfr __at 0x81 SP;
__sfr __at 0x82 DPL; 
__sfr __at 0x83 DPH;  
__sfr __at 0x84 DPL1; 
__sfr __at 0x85 DPH1;
__sfr __at 0x92 DPSEL; 
__sfr __at 0xD0 PSW; 
__sfr __at 0xE0 ACC; 
__sfr __at 0xF0 B; 

/* Power */
__sfr __at 0x87 PCON; 
__sfr __at 0xF8 PWRCON0;
__sfr __at 0xF9 PWRCON1;
__sfr __at 0xFB PWRCON2;
__sfr __at 0xFC PWRCON3;
__sfr __at 0xFE PWRCON4;
__sfr __at 0xFD PWRSTAT;

/* Clock */
__sfr __at 0x8E CKCON; 
__sfr __at 0xA6 RCCON;
__sfr __at 0xB0 CLKCON0;
__sfr __at 0xB1 CLKCON1;

/* Reset */
__sfr __at 0xA0 RESETS;

/* watchdog */
__sfr __at 0x86 WDTCON;

/* Charger */
__sfr __at 0xB6 CHGCON0;
__sfr __at 0xB2 CHGCON1;
__sfr __at 0xB3 CHGCON2;
__sfr __at 0xB5 CHGCON3;
__sfr __at 0x9F CHGCON4;
__sfr __at 0xB4 CHGCON5;
__sfr __at 0xB7 CHGSTAT;
__sfr __at 0xFF BATSTAT;

/* I/O port */
__sfr __at 0x80 P0DAT;
__sfr __at 0x80 P0;         // Dummy name
__sfr __at 0x95 P0MOD;
__sfr __at 0x96 P0PU;
__sfr __at 0x97 P0PD;
__sfr __at 0x90 P1DAT;
__sfr __at 0x90 P1;
__sfr __at 0x91 P1MOD;
__sfr __at 0x93 P1OM;
__sfr __at 0x94 P1PUPD;
__sfr __at 0xA7 PWKCTL;
__sfr __at 0xAA PDRV0;
__sfr __at 0xAF PDRV1;
__sfr __at 0xAB MFP0;
__sfr __at 0xAC MFP1;
__sfr __at 0xAD MFP2;
__sfr __at 0xAE MFP3;


/* Interrupt */
__sfr __at  0xA8 INTCON0;
__sfr __at  0xB8 INTCON1;
__sfr __at  0xC0 INTCON2;
__sfr __at  0xA9 EINTCON;
__sfr __at  0xB9 INTPRIO;


/* Timer */
__sfr __at 0x88 TCON;
__sfr __at 0xA1 TCON1;
__sfr __at 0x89 TMOD;
__sfr __at 0x8A TL0;
__sfr __at 0x8B TL1;
__sfr __at 0x8C TH0;
__sfr __at 0x8D TH1;
__sfr __at 0xA2 TPDL0;
__sfr __at 0xA2 TBLNCON0;   // TPDL0/TBLNCON0
__sfr __at 0xA3 TPDH0;
__sfr __at 0xA4 TPDL1;
__sfr __at 0xA4 TBLNCON1;   // TPDL1/TBLNCON1
__sfr __at 0xA5 TPDH1;

__sfr __at 0xC8 T2CON;
__sfr __at 0xC1 T2MOD;
__sfr __at 0xC9 T2STAT;
__sfr __at 0xC2 T2D0;
__sfr __at 0xC2 TL2;        // dummy name
__sfr __at 0xC3 T2D1;
__sfr __at 0xC3 TRL2;       // dummy name
__sfr __at 0xC4 T2D2;
__sfr __at 0xC4 TCC0L;      // dummy name
__sfr __at 0xC5 T2D3;
__sfr __at 0xC5 TCC1L;      // dummy name
__sfr __at 0xC6 T2D4;
__sfr __at 0xC6 TCC2L;      // dummy name
__sfr __at 0xC7 T2D5;
__sfr __at 0xC7 TCC3L;      // dummy name
__sfr __at 0xCA T2D6;
__sfr __at 0xCA TCC0H;      // dummy name
__sfr __at 0xCA TH2_0;      // dummy name
__sfr __at 0xCB T2D7;
__sfr __at 0xCB TCC1H;      // dummy name
__sfr __at 0xCB TRH2_0;     // dummy name
__sfr __at 0xCC T2D8;
__sfr __at 0xCC TCC2H;      // dummy name
__sfr __at 0xCC TH2_1;      // dummy name
__sfr __at 0xCD T2D9;
__sfr __at 0xCD TCC3H;      // dummy name
__sfr __at 0xCD TRH2_1;     // dummy name

/* LCD */
__sfr __at 0xD7 LCDCON;

/* Serial */
__sfr __at 0x98 SCON;
__sfr __at 0x99 SBUF;
__sfr __at 0x9A SBR;

/* I2C */
__sfr __at 0xD1 IICCON;
__sfr __at 0xD2 IICSTAT;
__sfr __at 0xD3 IICADDR;
__sfr __at 0xD4 IICDAT;
__sfr __at 0xD5 IICDIV;

/* SDP */
__sfr __at 0xD8 SDPCON0;
__sfr __at 0xDF SDPCON1;
__sfr __at 0xD9 SDPNM;
__sfr __at 0xDA SDPDA;
__sfr __at 0xDB SDPDAT0;
__sfr __at 0xDC SDPDAT1;
__sfr __at 0xDD SDPDAT2;
__sfr __at 0xDE SDPDAT3;

/* ADC */
__sfr __at 0xE6 ADCCON0;
__sfr __at 0xE7 ADCCON1;
__sfr __at 0xF5 ADCCON2;
__sfr __at 0xF7 ADCCON3;

__sfr __at 0xE8 ADCCHEN;
__sfr __at 0xE1 ADCDAT0L;
__sfr __at 0xE9 ADCDAT1L;
__sfr __at 0xEA ADCDAT01H;
__sfr __at 0xEB ADCDAT2L;
__sfr __at 0xEC ADCDAT3L;
__sfr __at 0xED ADCDAT23H;
__sfr __at 0xEE ADCDAT4L;
__sfr __at 0xEF ADCDAT5L;
__sfr __at 0xF1 ADCDAT45H;
__sfr __at 0xF2 ADCDAT6L;
__sfr __at 0xF3 ADCDAT7L;
__sfr __at 0xF4 ADCDAT67H;

__sfr __at 0xBD DCMPCON0;
__sfr __at 0xBE DCMPCON1;
__sfr __at 0xBF DCMPNDATL;


/* CMP */
__sfr __at 0xBA CMPCON0;
__sfr __at 0xBB CMPCON1;
__sfr __at 0xBC CMPCON2;

/* PFOU */
__sfr __at 0xE2 PRCCON0;
__sfr __at 0xE3 PRCCON1;
__sfr __at 0xD6 PRCCON2;
__sfr __at 0xE4 PRCFREQL;
__sfr __at 0xE5 DLLCON0;
__sfr __at 0xCF DLLCON1;
__sfr __at 0x9B HPWMCON0;
__sfr __at 0x9C HPWMDZT0;
__sfr __at 0x9D HPWMDZT1;

__sfr __at 0x8F NOUSEREG;

/*
 * BIT Register
 */

/*  PSW   */
__sbit __at 0xD7 CY; 
__sbit __at 0xD6 AC; 
__sbit __at 0xD5 F0; 
__sbit __at 0xD4 RS1; 
__sbit __at 0xD3 RS0; 
__sbit __at 0xD2 OV; 
__sbit __at 0xD0 P; 

/* PWR_CTL0 */
__sbit __at 0xFC VKEYEN;
__sbit __at 0xFB PCHGEN;

/* CLKCON0 */
__sbit __at 0xB7 DSEN;
__sbit __at 0xB6 WDTWKEN;
__sbit __at 0xB0 SCLKSRC;

/* RESETS */
__sbit __at 0xA7 WDTCLR;
__sbit __at 0xA5 SSDF;
__sbit __at 0xA4 WDOF;
__sbit __at 0xA3 LVRF;
__sbit __at 0xA2 ABNF;
__sbit __at 0xA1 PINF;
__sbit __at 0xA0 PORF;

/* P0 */
__sbit __at 0x87 P0_7;
__sbit __at 0x86 P0_6;
__sbit __at 0x85 P0_5;
__sbit __at 0x84 P0_4;
__sbit __at 0x83 P0_3;
__sbit __at 0x82 P0_2;
__sbit __at 0x81 P0_1;
__sbit __at 0x80 P0_0;

/* P1 */
__sbit __at 0x97 P06WKF;
__sbit __at 0x96 P04WKF;
__sbit __at 0x95 P03WKF;
__sbit __at 0x94 P1_4;
__sbit __at 0x93 P1_3;
__sbit __at 0x92 P1_2;
__sbit __at 0x91 P1_1;
__sbit __at 0x90 P1_0;

/* INTCON0 */
__sbit __at 0xAF EA; 
__sbit __at 0xAE ECHG;
__sbit __at 0xAD ECMP;
__sbit __at 0xAB ELV;
__sbit __at 0xAA EOT;
__sbit __at 0xA9 EIIC;
__sbit __at 0xA8 EUART;

/* INTCON1 */
__sbit __at 0xBF ESDP; 
__sbit __at 0xBE ET0; 
__sbit __at 0xBD ET1; 
__sbit __at 0xBC ET2; 
__sbit __at 0xBB ET2C3; 
__sbit __at 0xBA ET2C2;
__sbit __at 0xB9 ET2C1;
__sbit __at 0xB8 ET2C0;

/* INTCON2 */
__sbit __at 0xC4 EOC;
__sbit __at 0xC3 EOV;
__sbit __at 0xC2 EADC;
__sbit __at 0xC1 EX1;
__sbit __at 0xC0 EX0;

/* TCON */
__sbit __at 0x8F TF1; 
__sbit __at 0x8E TR1;
__sbit __at 0x8D TPE1;
__sbit __at 0x8C TBLNE1;
__sbit __at 0x8B TF0;
__sbit __at 0x8A TR0;
__sbit __at 0x89 TPE0;
__sbit __at 0x88 TBLNE0; 

/* T2CON */
__sbit __at 0xCC TR2;
__sbit __at 0xCB TCCS3;
__sbit __at 0xCA TCCS2;
__sbit __at 0xC9 TCCS1;
__sbit __at 0xC8 TCCS0; 

/* SCON */
__sbit __at 0x9F PAREN;
__sbit __at 0x9E BRDSRC;
__sbit __at 0x9D BR8;
__sbit __at 0x9C REN;
__sbit __at 0x9B RER;
__sbit __at 0x9A BRPRE;
__sbit __at 0x99 TI;
__sbit __at 0x98 RI;

/* SDPCON0 */
__sbit __at 0xDF SDPERR;
__sbit __at 0xDE SDPIF;
__sbit __at 0xDF SDPCHECK;
__sbit __at 0xDC DMODE;
__sbit __at 0xDB MSTART;

/* ADCCHEN */
__sbit __at 0xEF VBATEN;
__sbit __at 0xEE IBATEN;
__sbit __at 0xED AN5EN;
__sbit __at 0xEC AN4EN;
__sbit __at 0xEB AN3EN;
__sbit __at 0xEA AN2EN;
__sbit __at 0xE9 AN1EN;
__sbit __at 0xE8 AN0EN;
#else
#error("error env!")
#endif

#endif  /* #ifndef __REG_SS881X_H__ */
