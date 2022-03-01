# 1. 功能说明
利用SS881X的定时器2给P06,P14,P15同时产生占空比和频率相同的PWM波，通过三口叠加实现I0口驱动能力的增加。

# 2. 实现步骤

1.设置SCLK和分频系数，该例程配置CLKCON0 为12M时钟源， T2CON分频系数为1，同时将TR2置1，打开定时器2。

2.设置spwm的固定频率：

(1) 寄存器装载值= 2^13 －TCLK频率 / 想要获得的spwm频率 / 分频系数；

(2)将得到的值低8位放入TRL2，高位中的bit8到bit10放入TRH0,bit11和bit12放入TRH1，一共正好13位；

3.设置spwm的占空比：

![image](./timer2-duty.gif)

(1)当想获得最大占空比100%时，比较值为定时器2的重载值；

 当想获得最小占空比0%时，比较值为定时器2的最大计数值；

 当想获得0%到100%中间的值时，比较值的计算公式为：2^13 - 重载值，本例程duty的范围为0到3000；

(2) 将得到duty的占空值的分别放入到TTC2L和TCC2H中，当TL2/TH2的值计数到和TCCxL/TCCxH的值相等的时候，会在CCx引脚发生电平翻转；

4.配置并使能相应的spwm I/O口，本例程是将P06、P14、P15分别配置为CC2，其中freq为4000，duty值为2000，占空比为66.7%。。

# 3. 代码编译

## 3.1 PlatformIO IDE

### 3.1.1 参考如下链接，搭建PlatformIO IDE的开发环境

http://www.sinhmicro.com.cn/index.php/more/blog/vscode-platformio-sinh51

### 3.1.2 在PlatformIO IDE中打开工程并编译

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

## 3.2 Keil C51 IDE

### 3.2.1 参考如下链接，搭建Keil C51 IDE的开发环境

http://www.sinhmicro.com/index.php/tool/software/debugger/sinh51_keil

### 3.2.2 在Keil C51 IDE中打开工程并编译

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

# 4. 测试步骤

## 4.1 通过模拟器测试
### 4.1.1 PlatformIO IDE

暂不支持。

### 4.1.2 Keil C51 IDE

![image](./timer2-cc2-multi-io-simulator.png)

1.编译并运行工程；

2.观察pwm的输出频率；

3.观察CC2输出的占空比。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 4.2.3 硬件调试

可以通过示波器观察P06、P14、P15的输出占空比，如图所示。

驱动能力的测试方法：IO口输出低，外加0.5V左右的模拟电池，观察模拟电池的功耗。

![image](./timer2-cc2-multi-io-test.jpg)









