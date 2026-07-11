#define  _MAIN_C
#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "main.h"

void main()
{
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	SmartCarForward(100, 130);//智能小车前进调节范围80-255,255最快
	while(1);
} 