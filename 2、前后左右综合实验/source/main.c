#define  _MAIN_C
#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "Delay.h"
#include "main.h"

void main()
{
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	SmartCarForward(100, 130);//智能小车前进调节范围80-255,255最快
	Delay1ms(2000);			//延时2秒
	SmartCarBack(100, 130); //智能小车后退
	Delay1ms(2000);			//延时2秒
	SmartCarLeft(100, 130); //智能小车左转
	Delay1ms(2000);			//延时2秒
	SmartCarRight(100, 130);//智能小车右转
	Delay1ms(2000);			//延时2秒
	SmartCarStops();//智能小车停车
	while(1);
} 