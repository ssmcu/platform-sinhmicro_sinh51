# 1. 功能说明
SS881X系列芯片有低速运行模式，该模式下系统被切换到低频时钟，高频时钟被关闭，除此之外，其他功能正常。

# 2. 功能实现

关闭看门狗，配置正常模式的高频工作模式，延迟等待高频稳定后关闭高频：

（1）配置CLKCON0寄存器，开启高频，SCLK为12M Hz，分频系数为1；

（2）延迟等待高频稳定，清除CLKCON0寄存器的bit0，开启低频，SCLK为32K Hz;

（3）配置RCCON寄存器，关闭高频使能位；

（4）将CKCON寄存器设置为合理值（否则可能会影响系统的性能），具体配置表为：

![image](.\配置表.png)

# 3. 代码编译

## 3.1 PlatformIO IDE

###### 暂不支持

### 3.1.1 参考如下链接，搭建PlatformIO IDE的开发环境

http://www.sinhmicro.com.cn/index.php/more/blog/vscode-platformio-sinh51

### 3.1.2 在PlatformIO IDE中打开工程并编译

暂不支持

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
![image](.\low-speed-test-simulator.gif)

1. 配置工程的调试选项为模拟器，编译工程。
2. 启动调试，打开system调试窗口。
3. 运行工程，可以看到系统时钟SCLK为32K Hz。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 4.2.3 硬件调试

可以通过模拟电池给开发板上电，观察到低速模式下低频的功耗为2.744mA。

<img src=".\low-speed-test-hardware.jpg" alt="image" style="zoom:33%;" />
