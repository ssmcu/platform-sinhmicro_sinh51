# 1. 功能说明
将P00和P01作为输入，P06和P07作为输出，根据P00的状态，控制P06输出相同的状态（注意：P06在模拟器上时可以正常根据P00的状态输出相同的状态，但在调试器使用时P06被作为SSDIO口用于数据传输，从而影响了P06其它功能的使用，P06不能根据P00的状态输出相同的状态，并且此时的P06一直输出高电平。如果接线时你将P17作为SSDIO时，此时P06可正常使用），根据P01的状态，控制P07输出相同的状态。

# 2. 代码编译

## 2.1 PlatformIO IDE

![](.\io_test-build.gif)

1. 导入io_test。
2. 调出“PROJECT TASKS”界面，单机Build编译。
3. 编译成功后，生成hex和bin文件。

## 2.2 Keil C51 IDE

### 2.2.1 参考如下链接，搭建Keil C51 IDE的开发环境

http://www.sinhmicro.com/index.php/tool/software/debugger/sinh51_keil

### 2.2.2 在Keil C51 IDE中打开工程并编译

![](.\io_test.gif)
1. 打开“io_test”目录。
2. 打开"prj-->keil"目录。
3. 打开“ss881x"工程文件。
4. 点击编译按钮，编译工程。
5. 生成”ss881x.bin"非加密固件。
6. 生成”ss881x_fw.bin"加密固件。
7. 编译生成的固件位于“Output”目录中。

# 3. 测试步骤

## 3.1 通过模拟器测试
### 3.1.1 PlatformIO IDE

暂不支持。

### 3.1.2 Keil C51 IDE
![](.\io_test-simulator.gif)
1. 编译工程。
2. 打开"Option-->Debug"界面。
3. 配置工程的调试选项为模拟器。
4. 启动调试。
5. 运行代码，通过I/O或LED模拟器观察到：当手动给P00/P01高电平的时候，P06/P07亮了，手动给P00/P01低电平的时候，P06/P07灭了。

## 3.2 通过开发板测试

### 3.2.1 参考如下链接，进行硬件连接

http://sinhmicro.com/index.php/tool/hardware/debugger/ssd8
![](.\hardware-link.jpg)

### 3.2.2 通过Flash_Tools烧录固件
![](.\io_test-burn.gif)
1. 打开Flash_Tools工具。
2. 点击“连接”按钮。
3. 在“文件选择”处，选择相应的固件。
4. 点击“烧录”按钮，查看烧录状态。

### 3.2.3 硬件调试
![](.\hardware-test.gif)
1. 使用USB B连接线将调试器与PC连接起来。
2. 点击Flash烧录软件，芯片状态下的“连接按钮”。
3. 将LED灯一端接P07，一端接地，当P01接VCC(高电平)时，观察灯亮，当P01不接VCC(低电平）时，观察灯灭。
