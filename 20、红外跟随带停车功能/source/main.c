/*
* 【编写时间】： 2019年8月1日
* 【作    者】： 清翔电子:01
* 【版    本】： 1.0
* 【网    站】： http://www.qxmcu.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ 
* 【实验平台】： QX-MCS51 单片机开发板 & QX-A51智能小车
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
* 【程序功能】： 循迹避障二合一
* 【使用说明】： 按下S2按键后智能小车执行物体跟随过程中与
				 被跟随物体距离过近停车，直到超出预设安全
				 距离后才继续前进。
* 【注意事项】： 请勿把LCD1602插接在主控板上，避障、超声波、马达控制的线需要接好
*/

#define  _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "ultrasonic.h"
#include "app.h"
#include "Servo.h"
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
	LeftSpeed	= 110;//设置左轮速度
	RightSpeed	= 110;//设置右轮速度
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	Timer1Init();//初始化定时器
	ServoFront(); //初始化舵机朝向
	keyscan();//按S2按键启动	
	while(1)
	{
		FollowAvoid(50);//红外物体跟随带停车功能，形参设置停车距离，单位：毫米
	}
} 