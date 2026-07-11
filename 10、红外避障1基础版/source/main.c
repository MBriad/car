#define  _MAIN_C
#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "Delay.h"
#include "app.h"
#include "main.h"

uchar LeftSpeed, RightSpeed;//设置左右轮速度
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
	/*小车速度设置80~255,255最快*/
	LeftSpeed	= 150;//左轮速度
	RightSpeed	= 150;//右轮速度
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	keyscan();//按S2按键启动
	while(1)
	{
		IR_Avoid2();//红外避障基础版	
	}
} 