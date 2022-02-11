/*--------------------------------------------------------------------------
SS882X.H

Header file for Sinh Micro SS882X microcontroller.
--------------------------------------------------------------------------*/

#ifndef __REG_SS882X_H__
#define __REG_SS882X_H__

/*
 * BYTE Register
 */

/* MCU Core */
sfr SP          = 0x81;
sfr DPL         = 0x82; 
sfr DPH         = 0x83;  
sfr PSW         = 0xD0; 
sfr ACC         = 0xE0; 
sfr B           = 0xF0; 

/* KEY&LED */
sfr LEDCON      = 0xAB;
sfr KEYCON0     = 0xAC;
sfr KEYCON1     = 0xAD;
sfr KEYCON2     = 0xAE;

/* SysTick */
sfr TICKCON     = 0x8F;

/* Power */
sfr PCON        = 0x87; 
sfr PWRCON0     = 0xE8;
sfr PWRCON1     = 0xE9;
sfr PWRCON2     = 0xEA;
sfr PWRSTAT     = 0xEB;

/* Clock */
sfr CKCON       = 0x8E; 
sfr RCCON       = 0x8A;
sfr CLKCON0     = 0x88;
sfr CLKCON1     = 0x89;

/* Reset */
sfr RESETS      = 0xA0;

/* watchdog */
sfr WDTCON      = 0x86;

/* Charger */
sfr CHGCON0     = 0xB0;
sfr CHGCON1     = 0xB1;
sfr CHGCON2     = 0xB3;
sfr CHGCON3     = 0xB4;
sfr CHGSTAT     = 0xB2;

/* Battery */
sfr BATSTAT     = 0xEA;

/* Boost */
sfr BSTCON0     = 0xB8;
sfr BSTCON1     = 0xB9;
sfr BSTCON2     = 0xBB;
sfr BSTCON3     = 0xBC;
sfr BSTCON4     = 0xBE;
sfr BSTCON5     = 0xBF;
sfr BSTSTAT     = 0xC7;

/* I/O port */
sfr P0DAT	    = 0x80;
sfr P0	        = 0x80; // Dummy name
sfr P0IE	    = 0x90;
sfr P0OE	    = 0x98;
sfr P0PUPD	    = 0x91;
sfr P01CON      = 0x92;
sfr P03CON      = 0x93;
sfr MFP0	    = 0x94;
sfr MFP1	    = 0x95;

/* Interrupt */
sfr INTCON0     = 0xA8;

/* Timer */
sfr TCON	    = 0xC0;
sfr TL          = 0xC1;
sfr TRL         = 0xC2;
sfr TC0L        = 0xC3;
sfr TC1L        = 0xC4;
sfr TSTAT	    = 0xC8;

/* CMP */
sfr CMPCON0     = 0xB5;
sfr CMPCON1     = 0xB6;
sfr CMPCON2     = 0xB7;
sfr VBCMPCON    = 0xEA;

sfr DBGREG      = 0x9F;

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

/* CLKCON0 */
sbit DSEN       = 0x8F;
sbit WDTWKEN    = 0x8D;
sbit BSTWKEN    = 0x8C;
sbit NDWKEN     = 0x8B;
sbit SCLKSRC    = 0x88;

/* RESETS */
sbit WDTCLR     = 0xA7;
sbit SSDF       = 0xA5;
sbit WDTF       = 0xA4;
sbit LVRF       = 0xA3;
sbit EXTF       = 0xA2;
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

/* P0IE */
sbit P07IE      = 0x97;
sbit P06IE      = 0x96;
sbit P05IE      = 0x95;
sbit P04IE      = 0x94;
sbit P03IE      = 0x93;
sbit P02IE      = 0x92;
sbit P01IE      = 0x91;
sbit P00IE      = 0x90;

/* P0OE */
sbit P07OE      = 0x9F;
sbit P06OE      = 0x9E;
sbit P05OE      = 0x9D;
sbit P04OE      = 0x9C;
sbit P03OE      = 0x9B;
sbit P02OE      = 0x9A;
sbit P01OE      = 0x99;
sbit P00OE      = 0x98;

/* INTCON0 */
sbit EA          = 0xAF;
sbit EDR         = 0xAB;
sbit ETICK       = 0xAA;
sbit ECMP        = 0xA9;
sbit ETIMER      = 0xA8;

/*  TCON  */
sbit TR         = 0xC4;
sbit TCCM1      = 0xC3; 
sbit TCCM0      = 0xC2; 
sbit TCCS1      = 0xC1; 
sbit TCCS0      = 0xC0; 

/*  TSTAT  */
sbit TF         = 0xC8; 

#endif
