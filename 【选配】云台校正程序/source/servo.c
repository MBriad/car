#include "config.h"
#include "Delay.h"
#include "Servo.h"
/*=================================================
*函数名称：ServoFront
*函数功能：云台向前转动
*调用：
*输入：
=================================================*/
void ServoFront()
{
	char i;
	for(i=0;i<10;i++)
	{	
		ServoPin = 1;
		Delay1550us();
		ServoPin = 0;
		Delay18450us();
	}
	delay(800);
}
/*=================================================
*函数名称：ServoLeft
*函数功能：云台向左转动
*调用：
*输入：
=================================================*/
void ServoLeft()
{
	char i;
	for(i=0;i<10;i++)
	{	
		ServoPin = 1;
		Delay2500us();
		ServoPin = 0;
		Delay17500us();
	}
	delay(800);
}
/*=================================================
*函数名称：ServoFront
*函数功能：云台向右转动
*调用：
*输入：
=================================================*/
void ServoRight()
{
	char i;
	for(i=0;i<10;i++)
	{	
		ServoPin = 1;
		Delay600us();
		ServoPin = 0;
		Delay19400us();
	}
	delay(800);
}