# 1. 功能说明
使用扩展寄存器EFR实现功能，本例程是利用EFR中EXTMFP0寄存器实现P15引脚输出高电平“1”。

# 2. 实现步骤

通过EFRADR和EFRDAT两个SFR寄存器，可以拓展256字节的EFR。访问方式为将要访问的EFR地址写入EFRADR寄存器，再通过读、写EFRDAT寄存器，就可以访问相应的EFR寄存器。因此本例程操作：

1.定义用到的EXTMFP0、PEXTCON0寄存器地址；

2.将所用到的EFR寄存器地址写入EFRADR中，并通过EFRDAT进行数据修改，设置P15引脚为GPIO口；

3.通过PEXTCON0 寄存器使读写P15引脚输出高电平“1”。

（EFR寄存器访问的时候，需要避免被中断打断后再次访问EFR寄存器，必要时应用程序可以在访问EFR寄存器的时候关中断）

# 3. 代码编译

## 3.1 PlatformIO IDE

和其它例程基本一致，不再详细说明，具体参考：

###### [led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 3.1.1 参考如下链接，搭建PlatformIO IDE的开发环境

http://www.sinhmicro.com.cn/index.php/more/blog/vscode-platformio-sinh51

### 3.1.2 在PlatformIO IDE中打开工程并编译

和其它例程基本一致，不再详细说明，具体参考：

###### [led-blink/doc/readme.md][led-blink/doc/readme.md]

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

![image](.\efr_io_test-simulator.gif)

1. 编译工程。
2. 打开"Option-->Debug"界面。
3. 配置工程的调试选项为模拟器。
4. 启动调试。
5. 运行工程，观察P15的引脚状态。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接（用杜邦线将P13和P03连接起来，P13引脚供电电压约4.4V）

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 4.2.3 通过在线调试查看效果

将代码烧录芯片后，通过硬件调试，将P15连接LED灯，观察LED的状态验证P15输出高电平。

<img src=".\efr_io_test-hardware.jpg" alt="image" style="zoom: 67%;" />



