# 1. 功能说明
通过P03引脚或者P14引脚以低电平触发中断，中断服务实现P00引脚状态翻转，模拟LED的闪动。

# 2. 功能实现

通过配置相关寄存器把P03和P14引脚复用为外部中断1引脚，并配置为低电平触发中断，在中断服务函数中，实现P00引脚状态翻转，即LED灯闪烁，

由于LED灯点亮之后还有余晖，在硬件调试上，很难看出LED闪烁，所以我们在中断服务函数内调用 _delay_ms(250); 进行一段延时。



/**

其他步骤请参考（platform-sinhmicro_sinh51\examples\ss881x\eint0-test）。

**/
