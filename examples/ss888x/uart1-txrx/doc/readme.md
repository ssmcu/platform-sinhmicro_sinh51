# 1. 功能说明
​		串口数据的收发。

# 2. 功能实现

（1）配置EXTMFP2设定P21为UART1TX，P22为UART1RX

（2）配置CLKCON2开启UART1时钟

（3）配置AFR_UART1_CTL0分频系数、校验位，使能使发送和接收

（4）配置AFR_UART1_STATE对应波特率的第9位、AFR_UART1_BRL波特率为的低8位

（5）（如果为查询方式则不需要）配置AFR_UART1_CTL1使能RXFIFO不为空中断、INT_CTRL3使能UART1中断、EA使能全局中断

 发送：AFR_UART1_TX_DATA寄存器完成数据的发送，之前对AFR_UART1_STATE寄存器的满标记进行判断，等待FIFO变换到未满状态则进行发送

 接收：AFR_UART1_RX_DATA寄存器完成数据的接收，对AFR_UART1_FIFO_CTL的接收数据计数进行读取，对接收数据判断连续读取的次数

**注意：数据格式以\r\n结尾(hex实质为0x0a、0x0d结尾，需勾选\r\n)，且单次符合代码设定的字符数内。**

# 3. 代码编译

## 3.1 PlatformIO IDE

### 3.1.1 参考如下链接，搭建PlatformIO IDE的开发环境

http://www.sinhmicro.com.cn/index.php/more/blog/vscode-platformio-sinh51

### 3.1.2 在PlatformIO IDE中打开工程并编译

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../../ss881x/led-blink/doc/readme.md)

## 3.2 Keil C51 IDE

### 3.2.1 参考如下链接，搭建Keil C51 IDE的开发环境

http://www.sinhmicro.com/index.php/tool/software/debugger/sinh51_keil

### 3.2.2 在Keil C51 IDE中打开工程并编译

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../../ss881x/led-blink/doc/readme.md)

# 4. 测试步骤

## 4.1 通过模拟器测试
### 4.1.1 PlatformIO IDE

暂不支持。

### 4.1.2 Keil C51 IDE
暂不支持。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

在开发板上将P21(UART1TX)引脚连接USB串口（USB-TTL模块）的RX，将P22(UART1RX)引脚连接USB串口（USB-TTL模块）的TX，MCU的GND连接USB串口（USB-TTL模块）的GND

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../../ss881x/led-blink/doc/readme.md)

### 4.2.3 硬件调试

![](./uart1-txrx.gif)

（1）烧录固件，打开串口调试助手（微软应用商店版本），设置对应的USB-TTL模块串口号、波特率、数据位、校验位、停止位、不勾选以十六进制显示，然后打开串口

（2）MCU平台每约2s发送"please input”字符

（3）发送（字符串）以\r\n结尾(hex实质为0x0a、0x0d结尾，本串口发送勾选\r\n)，MCU平台接收到字符并发送回来，以“send message:（字符串）”发送并显示于串口调试助手

（4）当发送字符超过代码设定字符数时（设定15），MCU平台返回字符串“err”

（5）当发送字符并非以\r\n结尾，MCU平台返回字符串“err”
