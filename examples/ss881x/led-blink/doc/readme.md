# 1. 功能说明
以大约1Hz的频率（高500ms、低500ms），拉高、拉低P00引脚，模拟LED的闪动。

# 2. 代码编译

## 2.1 PlatformIO IDE

## 2.2 Keil C51 IDE
![image](https://github.com/ssmcu/platform-sinhmicro_sinh51/blob/main/examples/ss881x/led-blink/doc/led-blink-build.gif)
1. 打开“blink-led”目录。
2. 打开"prj-->keil"目录。
3. 打开“ss881x.uvproj"工程文件。
4. 点击编译按钮，编译工程。
5. 生成”ss881x.bin"非加密固件。
6. 生成”ss881x_fw.bin"加密固件。
7. 编译生成的固件位于“Output”目录中。

# 3. 测试步骤

## 3.1 通过模拟器测试
### 3.1.1 PlatformIO IDE

### 3.1.2 Keil C51 IDE
![image](https://github.com/ssmcu/platform-sinhmicro_sinh51/blob/main/examples/ss881x/led-blink/doc/led-blink-simulator.gif)
1. 编译工程。
2. 打开"Option-->Debug"界面。
3. 配置工程的调试选项为模拟器。
4. 启动调试。
5. 在“Peripherals”标签中打开I/O模拟器。
6. 运行代码，通过I/O或LED模拟器观察执行效果。

## 3.2 通过开发板测试
