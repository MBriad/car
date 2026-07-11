#include "config.h"
#include "motor.h"

uchar LeftMotorSpeed;
uchar RightMotorSpeed;
/*=================================================
*函数名称：SmartCarForward
*函数功能：智能小车前进
*调用：
*输入：LeftSpeedVal：左电机速度，输入范围100-255
	   RightSpeedVal：右电机速度，输入范围100-255
	   255速度最快，100最慢
=================================================*/
void SmartCarForward(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
	LeftMotorGo;					//左电机前进
	RightMotorGo;					//右电机前进
}