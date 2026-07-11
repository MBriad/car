/*
* 【编写时间】： 2019年8月6日
* 【作    者】： 清翔电子:01
* 【版    本】： 1.7 优化超声波云台避障逻辑
* 【网    站】： http://www.qxmcu.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ 
* 【实验平台】： QX-MCS51 单片机开发板 & QX-A51智能小车
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
* 【程序功能】： 云台避障，超声波云台与红外避障，1602液晶显示距离
* 【使用说明】： 1、必须接上1602液晶显示器
				 2、请将接在主控板和小车底板上的P32-P35的4P杜邦线拔掉
				 3、再装不两条杜邦线，分别把小车底盘上P34接到主控板的P10上，P35接到主控板的P11上

				 液晶第一行显示云台测距方向，分别为D、F前方，L左面,R右面
				 第二行是显示的距离，单位毫米
				 可以通过这个显示信息来调节智能小车避障逻辑，理论上不同实验环境
				 下都需要调试才能达到理想效果。
				 执行逻辑app.c文件夹内PTZ_Avoid函数
* 【注意事项】： 云台不防撞
*/

#define  _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "LCD1602.h"
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
//	LeftSpeed	= 150;//设置左轮速度
//	RightSpeed	= 150;//设置右轮速度
	IntRegInit();//中断寄存器初始化
//	Timer0Init();//PWM调速初始化
	Timer1Init();//初始化定时器
	Init_LCD1602(); //LCD1602初始化
	ServoFront(); //初始化舵机朝向
	LCD1602_Dis_Str(0, 0, "Please press the"); //LCD1602写字符串
	LCD1602_Dis_Str(0, 1, "S2 to start"); //LCD1602写字符串请按下S2启动小车
	keyscan();//按S2按键启动
	LCD1602_Clear_Screen();//LCD1602清屏	
	while(1)
	{
//		PTZ_Avoid(300);//舵机云台避障，LCD1602显示距离,形参设置触发距离，单位：毫米
		My_TEST();
		My_TEST_2();
	}
} 