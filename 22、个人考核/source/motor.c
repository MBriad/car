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
	LeftMotorGo;					//左电机正转
	RightMotorGo;					//右电机正转
}
/*=================================================
*函数名称：SmartCarBack
*函数功能：智能小车后退
*调用：
*输入：LeftSpeedVal：左电机速度，输入范围100-255
	   RightSpeedVal：右电机速度，输入范围100-255
	   255速度最快，100最慢
=================================================*/
//void SmartCarBack(uchar LeftSpeedVal,uchar RightSpeedVal)
//{
//	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
//	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
//	LeftMotorBack;					//左电机反转
//	RightMotorBack;					//右电机反转
//}
/*=================================================
*函数名称：SmartCarLeft
*函数功能：智能小车左转
*调用：
*输入：LeftSpeedVal：左电机速度，输入范围100-255
	   RightSpeedVal：右电机速度，输入范围100-255
	   255速度最快，100最慢
=================================================*/
void SmartCarLeft(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
	LeftMotorStop;					//左电机停转
	RightMotorGo;					//右电机正转
}
/*小车左掉头，可以在自身长度范围内掉头*/
void SmartCarLeftTurn(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
	LeftMotorBack;					//左电机反转
	RightMotorGo;					//右电机正转
}
/*=================================================
*函数名称：SmartCarRight
*函数功能：智能小车右转
*调用：
*输入：LeftSpeedVal：左电机速度，输入范围100-255
	   RightSpeedVal：右电机速度，输入范围100-255
	   255速度最快，100最慢
=================================================*/
void SmartCarRight(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
	LeftMotorGo;					//左电机正转
	RightMotorStop;					//右电机停转
}
/*小车右掉头，可以在自身长度范围内掉头*/
void SmartCarRightTurn(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//设置左侧电机速度
	RightMotorSpeed= RightSpeedVal;	//设置右侧电机速的	
	LeftMotorGo;					//左电机正转
	RightMotorBack;					//右电机反转
}
/*=================================================
*函数名称：SmartCarStops
*函数功能：智能小车停车
*调用：
*输入：
=================================================*/
void SmartCarStops(void)
{	
	LeftMotorStop;					//左电机停转
	RightMotorStop;					//右电机停转
}
