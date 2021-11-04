# 1. 功能说明
使用比较输出cc0和cc1输出PWM波形，并加入死区功能

# 2. 实现步骤

首先是实现比较输出，需要配置HIRC和SCLK,复用cc0和ccc1功能。后在定时器中配置重载值，数据寄存器初值，比较值tcc,时钟分频和来源，比较输出的极性。 其关系是

​					   **(2^13 - TCCx-  1)/(2^13 - TR2)  =  占空比**

计时器从重载值开始，计数到TCCx 按照极性改变输出，计数到溢出时再输出相反的电平。

死区功能则是在PROU中进行配置 使能DLL并选择来源SCL，设置其频率，开启cc0/cc1死区插入功能。设置死区插入时间的档位（0-15）。

1.  系统时钟及引脚配置

   a)   使能HIRC

   b)   SCLK源头设定HIRC,SCLK分频设置为4

   c)   引脚复用P04为CC0, P10为CC1

2. 定时器2比较输出配置

   a)   设置定时器2从SCLK的分频系数

   b)   设置TCCS0,TSS1的比较输出极性

   c)   启动TCCM0,TCCM1的比较功能

   d)   设置比较寄存器TCC0,TCC1的值

   e)   设置数据寄存器的初值

   f)   设置重载值

   g)   开启定时器2

3. 可编程频率输出单元(PFOU)插入死区配置

   a)   选择DLL时钟源为SCLK，使能DLL控制

   b)   设置DLL频率，此处选择2-6M

   c)   使能高精度PWM(CC0/1)死区(Dead Zone)插入功能

   d)   设置CC0,CC1死区插入时间，此处16个档位可调


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
<img src="./test.gif" alt="image"  />

1. 编译工程。
2. 打开"Option-->Debug"界面。
3. 配置工程的调试选项为模拟器。
4. 启动调试。
5. 在“Peripherals”标签中打开PWM。
6. 运行代码，可以观察到Duty与设置相同。

## 4.2 通过开发板测试

### 4.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8

需要使用示波器两个通道分别连接P04,P10进行观察，可以分别调用和不调用PROU_deadzone_Init();的不同，此处展示正确的对比

<img src="./dead.gif" alt="image"  />

​                                                                                                                                插入死区

<img src="./no_dead.gif" alt="image"  />

​		                                                                                                                          不插入死区

### 4.2.2 通过Flash_Tools烧录固件

和其它示例基本一致，不再详细说明，具体请参考：

[led-blink/doc/readme.md](../../led-blink/doc/readme.md)







