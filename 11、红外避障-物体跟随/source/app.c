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
//void IR_Avoid2()
//{
//	if(UAvoidSensorLeft == 0)
//	{
//		SmartCarRight(LeftSpeed, RightSpeed);//右转	
//	}else if(UAvoidSensorRight == 0)
//	{
//		SmartCarLeft(LeftSpeed, RightSpeed);//左转		
//	}else
//	{
//		SmartCarForward(LeftSpeed, RightSpeed);//前进	
//	}
//}

/*====================================
函数名	：IR_Follow
参数	：无
返回值	：无
描述	：智能小车红外避障-物体跟随
====================================*/
void IR_Follow()
{
	if((FollowSensorLeft == 0) && (FollowSensorRight == 0))	//左右红外传感器都检测到物体，智能小车前进
	{
		SmartCarForward(LeftSpeed, RightSpeed);//前进
	}else if((FollowSensorLeft == 1) && (FollowSensorRight == 0))//左边未识别到障碍物并且右边识别到，智能小车右转
	{
		SmartCarRight(LeftSpeed, RightSpeed);//右转			
	}else if((FollowSensorLeft == 0) && (FollowSensorRight == 1))//左边识别到障碍物并且右边未识别到，智能小车左转
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//左转	
	}else if((FollowSensorLeft == 1) && (FollowSensorRight == 1))//左右都未识别到障碍物，智能小车停车
	{
		SmartCarStops();
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
