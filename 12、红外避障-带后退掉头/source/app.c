#include "config.h"
#include "timer_ISR.h"
#include "Delay.h"
#include "motor.h"
#include "app.h"
#include "main.h"

/*====================================
函数名	：IR_Avoid4
参数	：无
返回值	：无
描述	：智能小车红外避障-带后退掉头
====================================*/
void IR_Avoid4()
{
	if((AvoidSensorLeft == 0) && (AvoidSensorRight == 1))
	/*左边识别到障碍物并且右边未识别到，智能小车右转*/
	{
		SmartCarRight(LeftSpeed, RightSpeed);//右转	
	}else if((AvoidSensorLeft == 1) && (AvoidSensorRight == 0))
	/*左边未识别到障碍物并且右边识别到，智能小车左转*/
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//左转		
	}else if((AvoidSensorLeft == 0) && (AvoidSensorRight == 0))	
	/*左右红外传感器都检测到物体，智能小车先停车后退再原地左转*/
	{
		SmartCarStops();//停车
		Delay1ms(100);//延时100ms
		SmartCarBack(LeftSpeed, RightSpeed);//后退
		Delay1ms(50);//延时50ms
		SmartCarLeftTurn(LeftSpeed, RightSpeed);//原地左转
		Delay1ms(50);//延时50ms		
	}else //否则前进
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
