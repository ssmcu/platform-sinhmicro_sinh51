/*--------------------------------------------------------------------------
SS880X.H

Header file for Sinh Micro SS881X microcontroller.
--------------------------------------------------------------------------*/

#ifndef __REG_SS881X_H__
#define __REG_SS881X_H__

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
sfr PCON        = 0x87; //0:空闲模式使能 1:待机模式使能 5:IOWK3 STOP唤醒引脚选择 0,P07 1,P20; 6:IOWK2 STOP唤醒引脚选择 0,P06 1,P02 7:IOWK0 STOP唤醒引脚选择 0,P03 1,P01
sfr PWRCON0     = 0xF8;	//3:内置LDO使能 4:模拟按键检测使能
sfr PWRCON1     = 0xF9;	//0:DCIN过压门限 1:DCIN低电压使能LDO 2:DCIN 过压检测使能
sfr PWRCON2     = 0xFB;	//0:VDD低电压检测使能 1:模拟按键唤醒标志 2:VDD低电压复位使能 5-3:VDD低电压门限 7-6:VDD低电压复位设置
sfr PWRCON3     = 0xFC;	//1:VIN过流保护使能 5-3:VIN过流电流设置 6:VIN过压电压设置 7:VIN过压保护使能
sfr PWRCON4     = 0xFE;	//0:过温中断标志 1:超高温即恢复门限 2:过温即恢复门限 3:过温检测使能 5:DCIN唤醒标志 6:VIN输入使能 7:VIN输入状态
sfr PWRSTAT     = 0xFD;	//0:DCIN输入电压正常标志 1:模拟按键检测状态 2:DCIN过压中断标志 3:VIN输入电压正常标志 4:VDD低电压中断标志 5:VIN过流中断标志

/* Clock */
sfr CKCON       = 0x8E; //6-4: 等待周期 = WaitCycle + 1
sfr RCCON       = 0xA6;	//0:高频RC使能; 1:高频RC稳定标志; 2:高频RC展频使能
sfr CLKCON0     = 0xB0;	//0:SCLK时钟源 0:LORC 1:HIRC; 3-1:SCLK分频系数 000->111; 6:WTDG作为待机唤醒源使能
sfr CLKCON1     = 0xB1;	//0:I2C时钟使能; 1:SDP时钟使能; 2:CMP时钟使能; 3:ADC&Cherger时钟使能; 4:可编程频率输出单元(PFOU)时钟使能; 6:I2C复位控制 7:SDP复位控制
sfr CLK_CTL2    = 0x92;	
/* Reset */
sfr RESETS      = 0xA0; //0:上电复位标志; 1:外部引脚复位标志; 2:软件异常复位标志; 3:VDD低电压复位标志 4:看门狗溢出复位标志 5:调试器复位标志 6:过温复位标志 7:喂狗

/* watchdog */
sfr WDTCON      = 0x86; //3-0:使能 1010en,0101dis; 6-4溢出时间 000-110(8s,4s,2s,1s,500ms,250ms,125ms,62.25ms); 7:使能后空闲是否工作

/* Charger */	//充电管理单元
sfr CHGCON0     = 0xB6; //0:charger使能; 1:强制充电使能; 3-2:充电超时时间 00-11 8h-48h; 7-4:恒流电流 0000-1111 45mA一档
sfr CHGCON1     = 0xB2;	//0:使能I<ISTOP停止充电; 1:充电温度环路使能 2:DCIN欠压环路使能; 7-3:恒压电压 00000-11111 1.5v-4.8v
sfr CHGCON2     = 0xB3;	//1-0:ISTOP 01 ISET*5%,11 ISET*10%; VSTOP:00-11 90mV-15mV 5-4:环路温度阈值: 00-11 95°C-125°C 7-6:DCIN欠压环路电压阈值 00-11 4.4V-4.7V
sfr CHGCON3     = 0xB5;	//1:充电模式: 0小电流(1/4) 1正常模式; 3-2:Charger模块工作模式 10-CHG模式 11-LDO模式; 7:增大电流200mA使能
sfr CHGCON4     = 0x9F;	//0:间歇恒压充电使能; 1:充满/超时中断使能; 2:回充功能使能; 5:DCIN插入中断位; 6:DCIN从待机模式唤醒使能; 7:DCIN唤醒方式 0拔出/接入唤醒 1接入状态唤醒
sfr CHGCON5     = 0xB4;	//
sfr CHGSTAT     = 0xB7;	//3:正在充电标志; 4:充满标志; 5充电超时标志 6:涓流状态标志 7:充电/超时中断标志
sfr BATSTAT     = 0xFF;//

/* I/O port */
sfr P0DAT	    = 0x80;	//P0 数据寄存器,复位时i/o为输入模式,输出模式默认输出1
sfr P0	      = 0x80; // Dummy name
sfr P0MOD	    = 0x95;	//P0 0,输出模式 1,输入模式
sfr P0PU	    = 0x96;	//P0 上拉使能 
sfr P0PD	    = 0x97;	//P0 下拉使能	(如果同时使能上拉下拉,存在漏电;对所有功能有效,切换时要配置好)
sfr P1DAT	    = 0x90;	//P1 数据寄存器 4-0:P1数据 5:P03唤醒标志 6:P04唤醒标志 7:P06唤醒标志
sfr P1	      = 0x90;
sfr P1MOD	    = 0x91;	//P1 4-0:输入输出模式 5:P03唤醒使能 6:P04唤醒使能 7:P06唤醒使能
sfr P1OM	    = 0x93;	//P1 输出模式 4-0: 0,推挽 1,开漏; 5:P03唤醒电平; 6:P04唤醒电平 7: P07驱动模式 0,正常(5mA) 1,增强 由PDRV0/V1配置
sfr P1PUPD	  = 0x94;	//P1上下拉 3-0:下拉使能 7-4 上拉使能 (P14在 PDRV0)
sfr PWKCTL    = 0xA7;	//P07/P11唤醒配置 2-0:P07唤醒模式 5-3:P11唤醒模式 6:P07唤醒标志 7:P11唤醒标志
sfr PDRV0     = 0xAA;	//驱动能力配置 0:P0[3:0] 0,弱驱动(5mA) 1,普通驱动(10mA) 2-1:P07源电流 00,20mA 01,40mA 3:P1[3:0] 0,弱驱动(5mA) 1,普通驱动(10mA); 4:P14驱动能力  5:P14下拉使能; 6: P14上拉使能
sfr PDRV1     = 0xAF;	//1-0: P04灌电流 3-2:P05灌电流 5-4:P06灌电流 7-6:P07灌电流
sfr MFP0	    = 0xAB;	//复用
sfr MFP1	    = 0xAC;	//复用
sfr MFP2	    = 0xAD;	//复用
sfr MFP3	    = 0xAE;	//二级复用关系


/* Interrupt */
sfr INTCON0     = 0xA8;	//.
sfr INTCON1     = 0xB8;	//.
sfr INTCON2     = 0xC0;	//.
sfr INTEN0      = 0xA8;	//中断使能 0:UART 1:I2C 2:系统过温 3:VDD低电压 4:触摸传感器 5:比较器 6:Charger 7:总开关
sfr INTEN1      = 0xB8;	//中断使能 0:TIM2捕获0; 1:TIM2捕获1; 2:TIM2捕获2; 3:TIM2捕获3; 4:TIM2计数; 5:TIM1计数; 6:TIM0计数 7:SDP
sfr INTEN2      = 0xC0;	//中断使能 0:EXTI0; 1:EXTI1; 2:ADC; 3:DCIN; 4:VIN过流; 5:SysTick; 6:ESPP 
sfr EINTCON     = 0xA9;	//外部中断 触发方式,中断标志
sfr INTPRIO     = 0xB9;	//中断优先级 1-0 Group0.....7-6 Group3  00最低,11最高


/* Timer */
sfr TCON	    = 0x88; //小TIM1大TIM0  4,0:呼吸模式启动; 5,1:PWM输出启动 6,2:定时器启动; 7,3:定时器溢出标志
sfr TCON1	    = 0xA1;	//小TIM1大TIM0 	4,0:PWM极性 0高 1低 7-5,3-1:SCLK分频系数
sfr TMOD	    = 0x89;	//小TIM1大TIM0	5-4,1-0:模式; 6,2: 0,定时器 1,计数器; 7,3: 0,(TCON 6,2)TRx置1,定时器被允许 1,EINTx在高电平期间TRx置1,定时器北云希
sfr TL0       = 0x8A;//..
sfr TL1       = 0x8B;//..
sfr TH0       = 0x8C;//..
sfr TH1	      = 0x8D;//..数据寄存器
sfr TPDL0     = 0xA2;//...
sfr TBLNCON0  = 0xA2; //.... 
sfr TPDH0	    = 0xA3;		//...
sfr TPDL1     = 0xA4;	//....(TCON 5,1)TBLNEx=1,有意义. 3-0:呼吸灯Q值 0000-0010,2,4,8; 7-4:呼吸灯周期: 0000,4s 0001,8s
sfr TBLNCON1  = 0xA4; // TPDL1/TBLNCON1
sfr TPDH1	    = 0xA5;		//...占空比寄存器 (TCON 5,1)TBLNEx=0,有意义. 13位时,H高8位,L低5位

sfr T2CON	      = 0xC8;	//3-0:比较/捕获极性 0高电平有效 1低电平有效/0下降沿捕获 1上升沿捕获; 4:使能; 7-5:SCLK分频  
sfr T2MOD	      = 0xC1;	//?????????
sfr T2STAT	    = 0xC9;	//状态寄存器 3-0:CCx捕获标志; 4:TIM2溢出标志 
sfr T2D0        = 0xC2;	//.
sfr TL2	        = 0xC2; // dummy name
sfr T2D1        = 0xC3;	//.
sfr TRL2        = 0xC3; // dummy name
sfr T2D2        = 0xC4;	//.
sfr TCC0L       = 0xC4; // dummy name
sfr T2D3        = 0xC5;	//.
sfr TCC1L       = 0xC5; // dummy name
sfr T2D4        = 0xC6;	//.
sfr TCC2L       = 0xC6; // dummy name
sfr T2D5        = 0xC7;	//.
sfr TCC3L       = 0xC7; // dummy name
sfr T2D6        = 0xCA;	//.
sfr TCC0H       = 0xCA; // dummy name
sfr TH2_0       = 0xCA; // dummy name
sfr T2D7        = 0xCB;	//.
sfr TCC1H       = 0xCB; // dummy name
sfr TRH2_0      = 0xCB; // dummy name
sfr T2D8        = 0xCC;	//.
sfr TCC2H       = 0xCC; // dummy name
sfr TH2_1       = 0xCC; // dummy name
sfr T2D9        = 0xCD;	//.数据/重载/捕获/比较 参考datesheet 13.3.5.3
sfr TCC3H       = 0xCD; // dummy name
sfr TRH2_1      = 0xCD; // dummy name

/* LCD */
sfr LCDCON      = 0xD7;	//0:使能; 2-1:驱动电流(VLCD5V) 00-11 75uA,150uA,300uA,600uA

/* Serial */
sfr SCON        = 0x98;	//0:接收中断标志 1:发送中断标志 2:波特率分频 3:接收错误标志 4:接收使能 5:波特率计算9位数据的最高位 6波特率source 7偶校验使能
sfr SBUF        = 0x99;	//数据寄存器 RX和TX同一个地址空间 一个只读一个只写
sfr SBR         = 0x9A;	//波特率配置寄存器低8位

/* I2C */
sfr IICCON      = 0xD1;	// 0：使能; 1:主从模式 3：上拉；5-4：主模式命令 6：总线控制位，写1触发
sfr IICSTAT     = 0xD2;	// 0: 错误；1：读写状态 2：停止信号 3：起始信号 4：发送、接收ack/nack; 5:中断标志 6：传输完成标志
sfr IICADDR     = 0xD3;	// 0:主机发送完成标志 7-1：从机地址
sfr IICDAT      = 0xD4;	//  发送/接收数据
sfr IICDIV      = 0xD5;	// 5-0:时钟分频 

/* SDP */
sfr SDPCON0	    = 0xD8;	// 2-1:数据派发的单位，即数据量 3：master数据派发启动控制 4：模式 0从1主 5：是否check 6:SDP中断标志 7：错误标志
sfr SDPCON1	    = 0xDF;	// 6-0:SDP分频系数 SCLK/8/(CLKDIV+1); 7: 0,硬件派发 1，软件派发 
sfr SDPNM	      = 0xD9;	// masteer:节点个数软件写入 slave:排序编号，自动写入
sfr SDPDA	      = 0xDA;	// master有效，5-0：TMODE=0:通过该地址读取发送的slave数据 
sfr SDPDAT0	    = 0xDB;	//.
sfr SDPDAT1	    = 0xDC;	//.
sfr SDPDAT2	    = 0xDD;	//.
sfr SDPDAT3	    = 0xDE;	//.数据寄存器 MASTER:TMODE=1,将要派发的数据;  SLAVE: 接收的数据

/* ADC */
sfr ADCCON0     = 0xE6; //3-1:求均值样本个数 5-4：采样时钟 6：连续、单次 7：单次采样开始
sfr ADCCON1     = 0xE7; //0: 中断标志 2-1：NTC电流源电流 5：NTC使能 6：中断使能
sfr ADCCON2     = 0xF5; // 0:AN4,AN5差分使能 1：开启ADC输入buffer 3：AN2中心电平 0，1.5 1，2.6； 3：AN3中心电平 0，1.5 1，2.6； 6:AN7中心电平 0，1.5 1，2.6；
sfr ADCCON3     = 0xF7;	//0: AN4: 0,微电压 1，正常； 1: AN5: 0,微电压 1，正常； 2：AN4中心电平 0，1.5 1，2.6； 3：AN5中心电平 0，1.5 1，2.6；4：VOFFSET 0,VEREF 1,GND; 7:GAIN0 (增益配置)
//没有ADDCCON4?

sfr ADCCHEN     = 0xE8;	//0:电池电压 1:充电电流 2:AN2 3:AN3 4:AN4 5:AN5 6:VOFFSET 7:AN7
sfr ADCDAT0L    = 0xE1; //ADC0(VBAT)低8位
sfr ADCDAT1L	  = 0xE9;	//通道1（IBART_CHG）数据寄存器低8位
sfr ADCDAT01H   = 0xEA;	//3-0: 通道0（VBAT）数据寄存器高4位； 7-4：通道1（IBART_CHG）数据寄存器高4位
sfr ADCDAT2L	  = 0xEB;	//通道2数据寄存器低8位
sfr ADCDAT3L	  = 0xEC;	//通道3数据寄存器低8位
sfr ADCDAT23H   = 0xED;	//3-0:通道2数据寄存器高4位 7-4：通道3数据寄存器高4位
sfr ADCDAT4L	  = 0xEE;	//通道4数据寄存器低8位
sfr ADCDAT5L	  = 0xEF;	//通道5数据寄存器低8位
sfr ADCDAT45H   = 0xF1;	//3-0:通道4数据寄存器高4位 7-4：通道5数据寄存器高4位
sfr ADCDAT6L	  = 0xF2;	//通道6数据寄存器低8位
sfr ADCDAT7L	  = 0xF3;	//通道7数据寄存器低8位
sfr ADCDAT67H   = 0xF4;	//3-0:通道7数据寄存器高4位 7-4：通道6数据寄存器高4位（此处手册错误）
//ADC中数据寄存器都为补码

sfr DCMPCON0    = 0xBD;	//0：比较器使能 1:结果 2：中断条件（>?:<） 3：中断使能 4：正端通道选择 5：中断标志
sfr DCMPCON1    = 0xBE;	//2-0: 负端来源 7-4：负端数据高4位
sfr DCMPNDATL   = 0xBF;	//负端数据低8位


/* CMP */
sfr CMPCON0     = 0xBA;	//0：比较器0使能 3-1：比较器0正端挡位 4：比较器1使能 7-5：3-1：比较器1正端挡位
sfr CMPCON1     = 0xBB;	//2-0:比较器0输出状态Debounce时间 6-4:比较器1输出状态Debounce时间 
sfr CMPCON2     = 0xBC;	//10：比较器0中断条件 2：比较器0结果 3：比较器0中断标志 5-4：比较器1中断条件 6：比较器1结果 7：比较器1中断标志 

/* PFOU */
sfr PRCCON0     = 0xE2;	//4:PRC使能 7-6:PRC中心频率 00,1.7 01,2.4 10,3 11,3.3(MHz)
sfr PRCCON1     = 0xE3;	// 1-0:时钟分频 00,/1 01,/8 10,/16 11/32; 2:占空比调节使能(默认50%); 7-5:微调档位高3位 
sfr PRCCON2     = 0xD6;	// 0:展频使能 3-1:展频范围; 5-4:展频速度 6:展频模式 连续/断续
sfr PRCFREQL    = 0xE4;	//微调档位低8位 
sfr DLLCON0     = 0xE5;	//0:DLL使能 1:DLL时钟 0,PRCCLK 1,SCLK 2:4路是否一起微调 3:DLL成功锁定标志 7-4: CLKSRC=0:PFO占空比 CLKSRC=1: SMART PWM占空比
sfr DLLCON1     = 0xCF;	//4-3: DLL频率范围
sfr HPWMCON0    = 0x9B;	//0:高精度PWM CC0/CC0-3使能 1:高精度PWM CC1使能 2:高精度PWM CC0/1死区插入使能 3:高精度PWM CC2/3死区插入使能 7-4:微调  Smart PWM CC1占空比
sfr HPWMDZT0    = 0x9C;	//3-0:高精度PWM(CC0)死区插入时间 7-4:高精度PWM(CC1)死区插入时间
sfr HPWMDZT1    = 0x9D;	//3-0:高精度PWM(CC2)死区插入时间 7-4:高精度PWM(CC3)死区插入时间

//1.将要访问的EFR地址写入EFRADR 2.读写EFRDAT
/*
	I/0复用关系配置(EFR_12H),
	I/0复用关系配置(EFR_13H),
	I/0扩展控制(EFR_14H),
	I/0扩展控制(EFR_15H),
	I/0扩展控制(EFR_70H),
	I/0扩展控制(EFR_71H),
	Smart_PWM控制寄存器(EFR_50H),
	Smart_PWM保护输出寄存器(EFR_51H),
	Touch_Sensor使能(EFR_10H),
	Touch_Sensor控制(EFR_11H),
	Touch_Sensor状态0(EFR_1AH),
	Touch_Sensor状态1(EFR_1BH),
	Touch_Sensor中断配置/状态0(EFR_1CH),
	Touch_Sensor中断配置/状态1(EFR_1DH),
	Touch_Sensor中断配置/状态3(EFR_1EH),
	Touch_Sensor按键级别配置寄存器(EFR_20H--EFR_28H),
	Touch_Sensor基准值(低8位)(EFR_2EH),
	Touch_Sensor基准值(高4位)(EFR_2EH),
	Touch_Sensor采样值(EFR_30H--EFR_3BH),
	Touch_Sensor通道偏差(EFR_40H--EFR_4BH),
	EEPROM地址寄存器(EFR_00H),
	EEPROM数据寄存器(EFR_02H),
	EEPROM控制寄存器(EFR_02H),
*/
sfr EFRADR      = 0x84;
sfr EFRDAT      = 0x85;

sfr TICKCON     = 0x8F; //systick控制 0:使能; 4:溢出标志; 7-5:周期 000-111 10ms-1000ms

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
sbit AN7EN      = 0xEF;
sbit VOFFEN     = 0xEE;
sbit AN5EN      = 0xED;
sbit AN4EN      = 0xEC;
sbit AN3EN      = 0xEB;
sbit AN2EN      = 0xEA;
sbit IBATEN     = 0xE9;
sbit VBATEN     = 0xE8;


#endif
