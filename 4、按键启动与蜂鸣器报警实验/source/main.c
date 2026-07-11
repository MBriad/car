#define  _MAIN_C
#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "Delay.h"
#include "main.h"

void keyscan()
{
	for(;;)	//死循环
	{
		if(KEY_S2 == 0)// 实时检测S2按键是否被按下
		{
			Delay1ms(5); //软件消抖
			if(KEY_S2 == 0)//再检测S2是否被按下
			{
				while(!KEY_S2);//松手检测
				BUZZER_on;	//开启蜂鸣器
				Delay1ms(200);//200毫秒延时
				BUZZER_off;	//关闭蜂鸣器
				break;		//退出FOR死循环
			}
		}
	}	
}

void main()
{
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	keyscan();//按S2按键启动
	SmartCarForward(100, 130);//智能小车前进调节范围80-255,255最快
	Delay1ms(2000);			//延时2秒
	BUZZER_on;	//开启蜂鸣器
	Delay1ms(200);//200毫秒延时
	BUZZER_off;	//关闭蜂鸣器
	SmartCarStops();//停车
	while(1);
} 