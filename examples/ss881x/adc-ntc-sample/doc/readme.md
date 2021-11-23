# 1. 功能说明
SS881X利用ADC模块的AN2通道，通过内部20uA的电流源，连接外部NTC测量温度。本例程将是P03作为AN2通道，连接外部NTC测量温度。通过ADC 得到电压值，再算出电阻值，最后参考热敏电阻的数据手册查表得到电阻对应的温度。通过电压计算电阻的公式为： R(KΩ)=V(mv) /20

# 2. 功能实现

1. ADC和时钟配置：

（1）配置ADCCON0寄存器，定义ADC为连续模式,ADC采样时钟1MHz,ADC采样后滤波求均值样本个数128；

（2）配置CLKCON1寄存器，使能ADC；（先使能ADC时钟再进行其它寄存器配置）

（3）配置ADCCHEN寄存器使AN2通道使能；

（4）配置ADCCON1，将NTC使能；

（5）配置ADCCON2，AN2通道中心电平为2600（2.6V）。

2.ADC值的读取：

（1）取ADC值，将12位补码转换成16位补码；

（2）将取出的ADC值加上中心电平得到电压值。

# 3. 代码编译

## 3.1 PlatformIO IDE

和其它例程基本一致，不再详细说明，具体参考：

###### [led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 3.1.1 参考如下链接，搭建PlatformIO IDE的开发环境

http://www.sinhmicro.com.cn/index.php/more/blog/vscode-platformio-sinh51

### 3.1.2 在PlatformIO IDE中打开工程并编译

和其它例程基本一致，不再详细说明，具体参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

## 3.2 Keil C51 IDE

### 3.2.1 参考如下链接，搭建Keil C51 IDE的开发环境

http://www.sinhmicro.com/index.php/tool/software/debugger/sinh51_keil

### 3.2.2 在Keil C51 IDE中打开工程并编译

和其他例程基本一致，不在详细说明，具体参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

# 4. 测试步骤

## 4.1 通过模拟器测试
### 4.1.1 PlatformIO IDE

暂不支持。

### 4.1.2 Keil C51 IDE

![image](.\adc_ntc_sample-simulator.gif)

1. 编译工程。
2. 打开"Option-->Debug"界面。
3. 配置工程的调试选项为模拟器。
4. 启动调试，观察vbat_mv的值是否与AN2通道的值一样。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

### 4.2.2 通过Flash_Tools烧录固件

1. 打开Flash_Tools工具。
2. 点击“连接”按钮。
3. 选择相应的固件,固件位于“Output”目录中。
4. 点击“烧录”按钮，查看烧录状态。

### 4.2.3 硬件调试

实际电路搭配如图所示，AN2通道接NTC温度测量，在keil硬件仿真中读取电压值，根据 R(KΩ)=V(mv) /20，得到电阻值，最后参考热敏电阻的数据手册查表得到电阻对应的温度。

![image](.\adc_ntc_sample-电路图.png)
