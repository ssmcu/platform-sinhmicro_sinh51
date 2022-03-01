#ifndef __SS888X_H__
#define __SS888X_H__

/* 0x80~0x87 */
sfr P0_DT = 0x80;
sfr SP = 0x81;
sfr DPL = 0x82;
sfr DPH = 0x83;
sfr EFR_ADR = 0x84;
sfr EFR_DAT = 0x85;
sfr WDTCON = 0x86;
sfr PCON = 0x87;

sfr P0DAT = 0x80;    /* Dummy Name */
sfr P0 = 0x80;       /* Dummy Name */
sfr EFR_ADDR = 0x84; /* Dummy Name */

/* 0x88~0x8F */
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0 = 0x8A;
sfr TL1 = 0x8B;
sfr TH0 = 0x8C;
sfr TH1 = 0x8D;
sfr CKCON = 0x8E;
sfr STKCTL = 0x8F;

sfr TICKCON = 0x8F; /* Dummy Name */

/* 0x90~0x97 */
sfr P1_DT = 0x90;
sfr P1_CTL = 0x91;
sfr CLK_CTL2 = 0x92;
sfr P1_OM = 0x93;
sfr P1_PUPD = 0x94;
sfr P0_CTL = 0x95;
sfr P0_PU = 0x96;
sfr P0_PD = 0x97;

sfr P1DAT = 0x90;   /* Dummy Name */
sfr P1 = 0x90;      /* Dummy Name */
sfr P1MOD = 0x91;   /* Dummy Name */
sfr CLKCON2 = 0x92; /* Dummy Name */
sfr P1OM = 0x93;    /* Dummy Name */
sfr P1PUPD = 0x94;  /* Dummy Name */
sfr P0MOD = 0x95;   /* Dummy Name */
sfr P0PU = 0x96;    /* Dummy Name */
sfr P0PD = 0x97;    /* Dummy Name */

/* 0x98~0x9F */
sfr UART0_CTL = 0x98;
sfr UART0_DATA = 0x99;
sfr UART0_BR = 0x9A;
sfr HPWM_CTL = 0x9B;
sfr HPWM_DT_CTL0 = 0x9C;
sfr HPWM_DT_CTL1 = 0x9D;
sfr HOSC_ANA_CTL = 0x9E;
sfr CHG_CTL1 = 0x9F;

sfr SCON = 0x98;     /* Dummy Name */
sfr SBUF = 0x99;     /* Dummy Name */
sfr SBR = 0x9A;      /* Dummy Name */
sfr HPWMCON0 = 0x9B; /* Dummy Name */
sfr HPWMDZT0 = 0x9C; /* Dummy Name */
sfr HPWMDZT1 = 0x9D; /* Dummy Name */
sfr CHGCON4 = 0x9F;  /* Dummy Name */

/* 0xA0~0xA7 */
sfr RESETS = 0xA0;
sfr TCON1 = 0xA1;
sfr TPDL0 = 0xA2;
sfr TBLNCON0 = 0xA2;
sfr TPDH0 = 0xA3;
sfr TPDL1 = 0xA4;
sfr TBLNCON1 = 0xA4;
sfr TPDH1 = 0xA5;
sfr RC_CTL = 0xA6;
sfr IOWK0_CTL = 0xA7;

sfr RCCON = 0xA6;  /* Dummy Name */
sfr PWKCTL = 0xA7; /* Dummy Name */

/* 0xA8~0xAF */
sfr INT_CTL0 = 0xA8;
sfr EINT_CTL = 0xA9;
sfr PAD_DRV0 = 0xAA;
sfr MFP0 = 0xAB;
sfr MFP1 = 0xAC;
sfr MFP2 = 0xAD;
sfr MFP3 = 0xAE;
sfr PAD_DRV1 = 0xAF;

sfr INT_CTRL0 = 0xA8;
sfr INTEN0 = 0xA8;  /* Dummy Name */
sfr INTCON0 = 0xA8; /* Dummy Name */
sfr EINTCON = 0xA9; /* Dummy Name */
sfr PDRV0 = 0xAA;   /* Dummy Name */
sfr PDRV1 = 0xAF;   /* Dummy Name */

/* 0xB0~0xB7 */
sfr CLK_CTL0 = 0xB0;
sfr CLK_CTL1 = 0xB1;
sfr CHG_ANA_CLT0 = 0xB2;
sfr CHG_ANA_CLT1 = 0xB3;
sfr CHG_ANA_CLT2 = 0xB4;
sfr CHG_ANA_CLT3 = 0xB5;
sfr CHG_CLT0 = 0xB6;
sfr CHG_STA0 = 0xB7;

sfr CLKCON0 = 0xB0; /* Dummy Name */
sfr CLKCON1 = 0xB1; /* Dummy Name */
sfr CHGCON1 = 0xB2; /* Dummy Name */
sfr CHGCON2 = 0xB3; /* Dummy Name */
sfr CHGCON5 = 0xB4; /* Dummy Name */
sfr CHGCON3 = 0xB5; /* Dummy Name */
sfr CHGCON0 = 0xB6; /* Dummy Name */
sfr CHGSTAT = 0xB7; /* Dummy Name */

/* 0xB8~0xBF */
sfr INT_CTL1 = 0xB8;
sfr INT_PRIO = 0xB9;
sfr CMP_CTL0 = 0xBA;
sfr CMP_CTL1 = 0xBB;
sfr CMP_CTL2 = 0xBC;
sfr DCP_CTL0 = 0xBD;
sfr DCP_CTL1 = 0xBE;
sfr DCPDTL = 0xBF;

sfr INTCON1 = 0xB8;   /* Dummy Name */
sfr INTPRIO = 0xB9;   /* Dummy Name */
sfr CMPCON0 = 0xBA;   /* Dummy Name */
sfr CMPCON1 = 0xBB;   /* Dummy Name */
sfr CMPCON2 = 0xBC;   /* Dummy Name */
sfr DCMPCON0 = 0xBD;  /* Dummy Name */
sfr DCMPCON1 = 0xBE;  /* Dummy Name */
sfr DCMPNDATL = 0xBF; /* Dummy Name */

/* 0xC0~0xC7 */
sfr INT_CTL2 = 0xC0;
sfr T2MOD = 0xC1;
sfr T2D0 = 0xC2;
sfr T2D1 = 0xC3;
sfr T2D2 = 0xC4;
sfr T2D3 = 0xC5;
sfr T2D4 = 0xC6;
sfr T2D5 = 0xC7;

sfr INTCON2 = 0xC0; /* Dummy Name */
sfr INTEN2 = 0xC0;  /* Dummy Name */
sfr TL2 = 0xC2;     /* Dummy Name */
sfr TRL2 = 0xC3;    /* Dummy Name */
sfr TCC0L = 0xC4;   /* Dummy Name */
sfr TCC1L = 0xC5;   /* Dummy Name */
sfr TCC2L = 0xC6;   /* Dummy Name */
sfr TCC3L = 0xC7;   /* Dummy Name */

/* 0xC8~0xCF */
sfr T2CON = 0xC8;
sfr T2STAT = 0xC9;
sfr T2D6 = 0xCA;
sfr T2D7 = 0xCB;
sfr T2D8 = 0xCC;
sfr T2D9 = 0xCD;
sfr PRC_ANAN_CTL = 0xCE;
sfr DLL_AND_CTL = 0xCF;

sfr TCC0H = 0xCA;   /* Dummy Name */
sfr TH2_0 = 0xCA;   /* Dummy Name */
sfr TCC1H = 0xCB;   /* Dummy Name */
sfr TRH2_0 = 0xCB;  /* Dummy Name */
sfr TCC2H = 0xCC;   /* Dummy Name */
sfr TH2_1 = 0xCC;   /* Dummy Name */
sfr TCC3H = 0xCD;   /* Dummy Name */
sfr TRH2_1 = 0xCD;  /* Dummy Name */
sfr DLLCON1 = 0xCF; /* Dummy Name */

/* 0xD0~0xD7 */
sfr PSW = 0xD0;
sfr IIC0_CTL = 0xD1;
sfr IIC0_STATE = 0xD2;
sfr IIC0_ADDR = 0xD3;
sfr IIC0_DAT = 0xD4;
sfr IIC0_DIV = 0xD5;
sfr PRC_CTL1 = 0xD6;
sfr LCD_CTL = 0xD7;

sfr IICCON = 0xD1;  /* Dummy Name */
sfr IICSTAT = 0xD2; /* Dummy Name */
sfr IICADDR = 0xD3; /* Dummy Name */
sfr IICDAT = 0xD4;  /* Dummy Name */
sfr IICDIV = 0xD5;  /* Dummy Name */
sfr PRCCON2 = 0xD6; /* Dummy Name */
sfr LCDCON = 0xD7;  /* Dummy Name */

/* 0xD8~0xDF */
sfr P2_DT = 0xD8;
sfr P2_CTL2 = 0xD9;
sfr NTC_CTL = 0xDA;
sfr IFR_ADR = 0xDB;
sfr IFR_DAT = 0xDC;
sfr HPWM_DT_CTL2 = 0xDD;
sfr HPWM_DT_CTL3 = 0xDE;
sfr INT_CTRL3 = 0xDF;

sfr P2DAT = 0xD8; /* Dummy Name */
sfr P2 = 0xD8;    /* Dummy Name */

/* 0xE0~0xE7 */
sfr ACC = 0xE0;
sfr ADCDAT0L = 0xE1;
sfr PRC_FRQ = 0xE2;
sfr PRC_CTL0 = 0xE3;
sfr PRC_ADJ = 0xE4;
sfr DLL_CTL = 0xE5;
sfr ADC_CTL0 = 0xE6;
sfr ADC_CTL1 = 0xE7;

sfr PRCCON0 = 0xE2;  /* Dummy Name */
sfr PRCCON1 = 0xE3;  /* Dummy Name */
sfr PRCFREQL = 0xE4; /* Dummy Name */
sfr DLLCON0 = 0xE5;  /* Dummy Name */
sfr ADCCON0 = 0xE6;  /* Dummy Name */
sfr ADCCON1 = 0xE7;  /* Dummy Name */

/* 0xE8~0xEF */
sfr ADCCH_CTL = 0xE8;
sfr ADCDAT1L = 0xE9;
sfr ADCDAT01H = 0xEA;
sfr ADCDAT2L = 0xEB;
sfr ADCDAT3L = 0xEC;
sfr ADCDAT23H = 0xED;
sfr ADCDAT4L = 0xEE;
sfr ADCDAT5L = 0xEF;

sfr ADCCHEN = 0xE8; /* Dummy Name */

/*	0xF0~0xF7	*/
sfr B = 0xF0;
sfr ADCDAT45H = 0xF1;
sfr ADCDAT6L = 0xF2;
sfr ADCDAT7L = 0xF3;
sfr ADCDAT67H = 0xF4;
sfr ADC_ANA_CTL0 = 0xF5;
sfr ADC_ANA_CTL1 = 0xF6;
sfr ADC_ANA_CTL2 = 0xF7;

sfr ADCCON2 = 0xF5; /* Dummy Name */
sfr ADCCON3 = 0xF7; /* Dummy Name */

/* 0xF8~0xFF */
sfr PWR_CTrel0 = 0xF8;
sfr TOPREG1 = 0xF9;
sfr TOPREG2 = 0xFA;
sfr LVDC = 0xFB;
sfr OVPREG_VIN = 0xFC;
sfr PWR_STA = 0xFD;
sfr OT_CTL = 0xFE;
sfr CHG_STA1 = 0xFF;

sfr PWRCON0 = 0xF8; /* Dummy Name */
sfr PWRCON1 = 0xF9; /* Dummy Name */
sfr PWRCON2 = 0xFB; /* Dummy Name */
sfr PWRCON3 = 0xFC; /* Dummy Name */
sfr PWRSTAT = 0xFD; /* Dummy Name */
sfr PWRCON4 = 0xFE; /* Dummy Name */
sfr BATSTAT = 0xFF; /* Dummy Name */

/* P1 */
sbit P06WKF = 0x97;
sbit P04WKF = 0x96;
sbit P03WKF = 0x95;
sbit P1_4 = 0x94;
sbit P1_3 = 0x93;
sbit P1_2 = 0x92;
sbit P1_1 = 0x91;
sbit P1_0 = 0x90;

/* SCON */
sbit BR8 = 0x9D;
sbit REN = 0x9C;
sbit RER = 0x9B;
sbit BRPRE = 0x9A;
sbit TI = 0x99;
sbit RI = 0x98;

/* PSW */
sbit CY = 0xD7;
sbit AC = 0xD6;
sbit F0 = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV = 0xD2;
sbit P = 0xD0;

/* PWR_CTL0 */
sbit VKEYEN = 0xFC;
sbit PCHGEN = 0xFB;

/* CLKCON0 */
sbit DSEN = 0xB7;
sbit WDTWKEN = 0xB6;
sbit SCLKSRC = 0xB0;

/* RESETS */
sbit WDTCLR = 0xA7;
sbit SSDF = 0xA5;
sbit WDOF = 0xA4;
sbit LVRF = 0xA3;
sbit ABNF = 0xA2;
sbit PINF = 0xA1;
sbit PORF = 0xA0;

/* P0 */
sbit P0_7 = 0x87;
sbit P0_6 = 0x86;
sbit P0_5 = 0x85;
sbit P0_4 = 0x84;
sbit P0_3 = 0x83;
sbit P0_2 = 0x82;
sbit P0_1 = 0x81;
sbit P0_0 = 0x80;

/* P2 P3 */
sbit P3_0 = 0xD8;
sbit P2_3 = 0xDB;
sbit P2_4 = 0xDC;
sbit P2_5 = 0xDD;
sbit P2_6 = 0xDE;
sbit P2_7 = 0xDF;

sbit BRDSRC = 0x9E;
sbit PAREN = 0x9F;

/* INTCON0 */
sbit EA = 0xAF;
sbit ECHG = 0xAE;
sbit ECMP = 0xAD;
sbit ELV = 0xAB;
sbit EOT = 0xAA;
sbit EIIC = 0xA9;
sbit EUART = 0xA8;

/* INTCON1 */
sbit ESDP = 0xBF;
sbit ET0 = 0xBE;
sbit ET1 = 0xBD;
sbit ET2 = 0xBC;
sbit ET2C3 = 0xBB;
sbit ET2C2 = 0xBA;
sbit ET2C1 = 0xB9;
sbit ET2C0 = 0xB8;

/* INTCON2 */
sbit ETICK = 0xC5;
sbit EOC = 0xC4;
sbit EOV = 0xC3;
sbit EADC = 0xC2;
sbit EX1 = 0xC1;
sbit EX0 = 0xC0;

/* TCON */
sbit TR1 = 0x8E;
sbit TF1 = 0x8F;
sbit TPE1 = 0x8D;
sbit TBLNE1 = 0x8C;
sbit TF0 = 0x8B;
sbit TR0 = 0x8A;
sbit TPE0 = 0x89;
sbit TBLNE0 = 0x88;

/* T2CON */
sbit TR2 = 0xCC;
sbit TCCS3 = 0xCB;
sbit TCCS2 = 0xCA;
sbit TCCS1 = 0xC9;
sbit TCCS0 = 0xC8;

/* SDPCON0 */
sbit SDPERR = 0xDF;
sbit SDPIF = 0xDE;
sbit SDPCHECK = 0xDF;
sbit DMODE = 0xDC;
sbit MSTART = 0xDB;

/* ADCCHEN */
sbit VBATEN = 0xEF;
sbit IBATEN = 0xEE;
sbit AN5EN = 0xED;
sbit AN4EN = 0xEC;
sbit AN3EN = 0xEB;
sbit AN2EN = 0xEA;
sbit AN1EN = 0xE9;
sbit AN0EN = 0xE8;

/* AFR */
#define AFR_P2_DT (*(volatile unsigned char idata*)0xF8)
#define AFR_P2_CTL2 (*(volatile unsigned char idata*)0xF9)
#define AFR_P2_PU (*(volatile unsigned char idata*)0xFA)
#define AFR_P2_PD (*(volatile unsigned char idata*)0xFB)
#define AFR_INFO_WRITEKEY (*(volatile unsigned char idata*)0xFC)
#define AFR_RESERVED1 (*(volatile unsigned char idata*)0xFD)
#define AFR_IO_OM_CTL3 (*(volatile unsigned char idata*)0xFE)
#define AFR_RESERVED2 (*(volatile unsigned char idata*)0xFF)

#define AFR_SSP_CON0 (*(volatile unsigned char idata*)0xF0)
#define AFR_SSP_CON1 (*(volatile unsigned char idata*)0xF1)
#define AFR_SSP_DAT (*(volatile unsigned char idata*)0xF2)
#define AFR_SSP_FIFOSTART (*(volatile unsigned char idata*)0xF3)
#define AFR_SSP_T_START (*(volatile unsigned char idata*)0xF4)
#define AFR_SSP_T_ZERO (*(volatile unsigned char idata*)0xF5)
#define AFR_SSP_T_ONE (*(volatile unsigned char idata*)0xF6)
#define AFR_SSP_T_STOP (*(volatile unsigned char idata*)0xF7)

#define AFR_SPIF_CTL (*(volatile unsigned char idata*)0xE8)
#define AFR_SPIF_STAT (*(volatile unsigned char idata*)0xE9)
#define AFR_SPI_DATCNT (*(volatile unsigned char idata*)0xEA)
#define AFR_SPI_DBG (*(volatile unsigned char idata*)0xEB)
#define AFR_P2730_PU_CTL (*(volatile unsigned char idata*)0xEC)
#define AFR_IOWK_STATE (*(volatile unsigned char idata*)0xED)
#define AFR_IOWK1_CTL (*(volatile unsigned char idata*)0xEE)
#define AFR_IOWK2_CTL (*(volatile unsigned char idata*)0xEF)

#define AFR_SPI_CTL0 (*(volatile unsigned char idata*)0xE0)
#define AFR_SPI_CTL1 (*(volatile unsigned char idata*)0xE1)
#define AFR_SPI_STAT (*(volatile unsigned char idata*)0xE2)
#define AFR_SPI_INTEN (*(volatile unsigned char idata*)0xE3)
#define AFR_SPI_INTSTA (*(volatile unsigned char idata*)0xE4)
#define AFR_SPI_CPR (*(volatile unsigned char idata*)0xE5)
#define AFR_SPI_TXD (*(volatile unsigned char idata*)0xE6)
#define AFR_SPI_RXD (*(volatile unsigned char idata*)0xE7)

#define AFR_UART1_CTL0 (*(volatile unsigned char idata*)0xD8)
#define AFR_UART1_CTL1 (*(volatile unsigned char idata*)0xD9)
#define AFR_UART1_STATE (*(volatile unsigned char idata*)0xDA)
#define AFR_UART1_BRL (*(volatile unsigned char idata*)0xDB)
#define AFR_UART1_TX_DATA (*(volatile unsigned char idata*)0xDC)
#define AFR_UART1_RX_DATA (*(volatile unsigned char idata*)0xDD)
#define AFR_USERID (*(volatile unsigned char idata*)0xDE)
#define AFR_UART1_FIFO_CTL (*(volatile unsigned char idata*)0xDF)

#define AFR_INFO_ADR (*(volatile unsigned char idata*)0xD0)
#define AFR_INFO_DAT (*(volatile unsigned char idata*)0xD1)
#define AFR_IIC1_CTL (*(volatile unsigned char idata*)0xD2)
#define AFR_IIC1_STA (*(volatile unsigned char idata*)0xD3)
#define AFR_IIC1_ADDR (*(volatile unsigned char idata*)0xD4)
#define AFR_IIC1_DATA (*(volatile unsigned char idata*)0xD5)
#define AFR_IIC1_DIV (*(volatile unsigned char idata*)0xD6)
#define AFR_IFR_STAT (*(volatile unsigned char idata*)0xD7)

#define AFR_RAMBIST (*(volatile unsigned char idata*)0xC8)
#define AFR_IO_OM_CTL1 (*(volatile unsigned char idata*)0xC9)
#define AFR_CHIPID0 (*(volatile unsigned char idata*)0xCA)
#define AFR_CHIPID1 (*(volatile unsigned char idata*)0xCB)
#define AFR_CHIPID2 (*(volatile unsigned char idata*)0xCC)
#define AFR_CHIPID3 (*(volatile unsigned char idata*)0xCD)
#define AFR_IO_OM_CTL2 (*(volatile unsigned char idata*)0xCE)
#define AFR_SINHID (*(volatile unsigned char idata*)0xCF)

#define AFR_TEST_CTL (*(volatile unsigned char idata*)0xC0)
#define AFR_VBGGAL_VAL (*(volatile unsigned char idata*)0xC1)
#define AFR_IREFCAL_VAL (*(volatile unsigned char idata*)0xC2)
#define AFR_HIRCCAL_VAL (*(volatile unsigned char idata*)0xC3)
#define AFR_LORCCAL_VAL (*(volatile unsigned char idata*)0xC4)
#define AFR_PRC0CAL_VAL (*(volatile unsigned char idata*)0xC5)
#define AFR_PRC1CAL_VAL (*(volatile unsigned char idata*)0xC6)
#define AFR_PRC2CAL_VAL (*(volatile unsigned char idata*)0xC7)

/* EFR */
#define EEADR (0x00)
#define EEDAT (0x01)
#define EECTL (0x02)
#define TPCTL0 (0x10)
#define TPCTL1 (0x11)
#define TPCTL2 (0x12)
#define TPCTL3 (0x13)
#define TKGPIO0 (0x14)
#define TKGPIO1 (0x15)
#define TPAN0 (0x16)
#define TPAN1 (0x17)
#define TPAN2 (0x18)
#define TPSTA0 (0x1A)
#define TPSTA1 (0x1B)
#define TPPEND0 (0x1C)
#define TPPEND1 (0x1D)
#define TPPEND2 (0x1E)
#define TP01CMPLV0 (0x20)
#define TP23CMPLV0 (0x21)
#define TP45CMPLV0 (0x22)
#define TP01CMPLV1 (0x23)
#define TP23CMPLV1 (0x24)
#define TP45CMPLV1 (0x25)
#define TP01CMPLV2 (0x26)
#define TP23CMPLV2 (0x27)
#define TP45CMPLV2 (0x28)
#define TPCHBVL (0x2E)
#define TPCHBVLH (0x2F)
#define TPCH0SPL (0x30)
#define TPCH0SPH (0x31)
#define TPCH1SPL (0x32)
#define TPCH1SPH (0x33)
#define TPCH2SPL (0x34)
#define TPCH2SPH (0x35)
#define TPCH3SPL (0x36)
#define TPCH3SPH (0x37)
#define TPCH4SPL (0x38)
#define TPCH4SPH (0x39)
#define TPCH5SPL (0x3A)
#define TPCH5SPH (0x3B)
#define TPCH0OSETL (0x40)
#define TPCH0OSETH (0x41)
#define TPCH1OSETL (0x42)
#define TPCH1OSETH (0x43)
#define TPCH2OSETL (0x44)
#define TPCH2OSETH (0x45)
#define TPCH3OSETL (0x46)
#define TPCH3OSETH (0x47)
#define TPCH5OSETL (0x48)
#define TPCH5OSETH (0x49)
#define TPCH6OSETL (0x4A)
#define TPCH6OSETH (0x4B)
#define PWMPT (0x50)
#define PTMFP (0x51)
#define CRC_STATE (0x58)
#define CRC_DATA0 (0x59)
#define CRC_DATA1 (0x5A)
#define CAR_LEN_L (0x5B)
#define CRC_LEN_H (0x5C)
#define PWR_CTL1 (0x5E)
#define LDO_CTL (0x60)
#define LDO_SFR (0x61)
#define LDO_TRIM (0x62)
#define RESETS1 (0x66)
#define BUART_CTL (0x68)
#define BUART_CTL1 (0x69)
#define OPA_CTL (0x6C)
#define OPA_CTL1 (0x6D)
#define NTC_TRIM (0x6E)
#define P2_CTL0 (0x70)
#define P2_CTL1 (0x71)
#define MFP4 (0x74)
#define MFP5 (0x75)
#define MFP6 (0x76)
#define MFP7 (0x77)

#endif