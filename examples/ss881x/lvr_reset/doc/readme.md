# 1. 功能说明
​	使用低电压复位功能。

# 2. 功能实现

​    此功能的配置都在PWRCON2寄存器中，注意低电压复位要开启低电压检测功能。

​    首先，配置低电压复位门限，再配置低电压检测门限，最后使能低电压检测和低电压复位功能。

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
暂不支持。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)

### 4.2.3 硬件调试

1. 使用USB B连接线将调试器与PC连接起来。

2. 点击Flash烧录软件，芯片状态下的“连接按钮”。

3. 使用杜邦线将BAT和VDD(VCC)连接起来

   <img src="./connect.gif" alt="image" style="zoom: 33%;" />

4. 将P00和P01分别连接到两个LED上，上电后P01闪烁

<img src="./work.gif" alt="image" style="zoom: 67%;" />



5. 将VCC(VDD)一端拔出后再插上，可以看到P00闪烁两次，表示读到低电压复位标志

<img src="./reset.gif" alt="image" style="zoom: 50%;" />
