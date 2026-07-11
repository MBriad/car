#include "config.h"
#include "timer_ISR.h"
#include "Delay.h"
#include "motor.h"
#include "app.h"
#include "main.h"

/*====================================
函数名	：IR_Avoid1
参数	：无
返回值	：无
描述	：智能小车红外避障-基础版
====================================*/
//void IR_Avoid1()
//{
//	if(AvoidSensorLeft == 0)
//	{
//		SmartCarRight(LeftSpeed, RightSpeed);//右转	
//	}else
//	{
//		SmartCarForward(LeftSpeed, RightSpeed);//前进	
//	}
//}
/*====================================
函数名	：IR_Avoid2
参数	：无
返回值	：无
描述	：智能小车红外避障-基础版
====================================*/
void IR_Avoid2()
{
	if((AvoidSensorLeft == 0) && (AvoidSensorRight == 1))
	{
		SmartCarRight(LeftSpeed, RightSpeed);//右转
		Delay1ms(100);	
	}else if((AvoidSensorLeft == 1) && (AvoidSensorRight == 0))
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//左转
		Delay1ms(100);		
	}else if((AvoidSensorLeft == 0) && (AvoidSensorRight == 0))
	{
		SmartCarRightTurn(LeftSpeed, RightSpeed);//原地右转	
		Delay1ms(100);	
	}else
	{
		SmartCarForward(LeftSpeed, RightSpeed);//前进	
	}
}

/*====================================
函数名	：IR_Tracking
参数	：无
返回值	：无
描述	：智能小车红外循迹
====================================*/
//void IR_Tracking()
//{
//		/*1为识别到黑线*/
//	if((TrackSensorLeft == 1) && (TrackSensorRight == 1))
//	{	
//		SmartCarForward(LeftSpeed, RightSpeed);//前进	
//	}else if((TrackSensorLeft == 0) && (TrackSensorRight == 1))
//	{
//		SmartCarRight(200, RightSpeed);//右转
//	}else if((TrackSensorLeft == 1) && (TrackSensorRight == 0))
//	{
//
//		SmartCarLeft(LeftSpeed, 200);//左转	
//	}
//}
