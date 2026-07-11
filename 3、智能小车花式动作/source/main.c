#define  _MAIN_C
#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "Delay.h"
#include "main.h"

void main()
{
	uchar i;
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	SmartCarForward(100, 130);//智能小车前进调节范围80-255,255最快
	Delay1ms(2000);			//延时2秒
	SmartCarBack(100, 130); //智能小车后退
	Delay1ms(2000);			//延时2秒
	/*间歇性前进*/
	for(i=0; i<8; i++)
	{
		SmartCarForward(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	/*间歇性后退*/
	for(i=0; i<8; i++)
	{
		SmartCarBack(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	/*左转与坦克掉头嵌套*/
	for(i=0; i<8; i++)
	{
		SmartCarLeft(100, 130);
		Delay1ms(400);
		SmartCarStops();
		Delay1ms(200);
		SmartCarRightTurn(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	/*右小转与坦克掉头嵌套*/
	for(i=0; i<8; i++)
	{
		SmartCarRight(100, 130);
		Delay1ms(400);
		SmartCarStops();
		Delay1ms(200);
		SmartCarLeftTurn(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	/*小车间歇性前进与左转*/
	for(i=0; i<8; i++)
	{
		SmartCarForward(100, 130);
		Delay1ms(400);
		SmartCarStops();
		Delay1ms(200);
		SmartCarLeft(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	/*间歇性前进与右转*/
	for(i=0; i<8; i++)
	{
		SmartCarForward(100, 130);
		Delay1ms(400);
		SmartCarStops();
		Delay1ms(200);
		SmartCarRight(100, 130);
		Delay1ms(200);
		SmartCarStops();
		Delay1ms(200);	
	}
	SmartCarForward(255, 60); //转圈
	Delay1ms(10000);
	SmartCarStops();//智能小车停车
	BUZZER = 0;	    //开蜂鸣器
	Delay1ms(1000);
	BUZZER = 1;		//关蜂鸣器
	while(1);
} 