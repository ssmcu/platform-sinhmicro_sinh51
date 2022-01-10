$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 2020-2030 Sinh Micro, Inc.
;  Version 1.00
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP_SS888X.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP_SS888X.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP_SS888X.OBJ  controls
;
;------------------------------------------------------------------------------
;
;  User-defined <h> Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
; <o> IDATALEN: IDATA memory size <0x0-0x100>
;     <i> Note: The absolute start-address of IDATA memory is always 0
;     <i>       The IDATA space overlaps physically the DATA and BIT areas.
; <o> XDATALEN: XDATA memory size <0x8000-0x833f>
;     <i> Note: The absolute start-address of XDATA memory is always 0
;     <i>       The IDATA space overlaps physically the DATA and BIT areas.

IDATALEN            EQU     0C0H
XDATALEN            EQU     340H
XEEPROM_LEN         EQU     7FH
XDATA_LEN_H         EQU     03H
XDATA_LEN_L         EQU     40H
XDATA_START_ADDR    EQU     8000H

;if CLR_XDATA_ALL = 1，clear 832Byte XDATA, CLR_XDATA_ALL = 0, clear 832 - 128 byte XDATA
CLR_XDATA_ALL       EQU     1H

;------------------------------------------------------------------------------
;
; <o> USECHIPID: If using FIRMWAREID to identify the firmware <0 or 1> 
;     <i> 0, not use; 1, use.
USEFIRMWAREID	EQU		0
; <o> FIRMWAREID0: firmware id byte0
; <o> FIRMWAREID1: firmware id byte1
; <o> FIRMWAREID2: firmware id byte2 
; <o> FIRMWAREID3: firmware id byte3
FIRMWAREID0		EQU		30H
FIRMWAREID1		EQU		38H
FIRMWAREID2		EQU		51H
FIRMWAREID3		EQU		39H

; Standard SFR Symbols 
ACC     DATA    0xe0
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

                NAME    ?C_STARTUP

?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1

                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

                CSEG    AT      0
?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:

;CLR XDATA
IF XDATALEN <> 0
                MOV     DPTR,#XDATA_START_ADDR
                CLR     A
IF CLR_XDATA_ALL = 1
                MOV     R7,A
                MOV     R6,A
ELSE
                MOV     R7,#XEEPROM_LEN
                MOV     R6,A
ENDIF
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                INC     R7
                CJNE    R7,#0x00,XDATA_JUDGE
                INC     R6
XDATA_JUDGE:    CJNE    R6,#XDATA_LEN_H,XDATALOOP
                CJNE    R7,#XDATA_LEN_L,XDATALOOP
ENDIF

;CLR IDATA
IF IDATALEN <> 0
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF
                MOV     SP,#?STACK-1
                LJMP    ?C_START

; Optional ROM-table for XC864 LIN-BSL
IF USEFIRMWAREID <> 0
		CSEG    AT      3FCH
		DB      FIRMWAREID0
		DB      FIRMWAREID1
		DB      FIRMWAREID2
		DB      FIRMWAREID3
ENDIF

                END
