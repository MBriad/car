#include "config.h"
#include "timer_ISR.h"
#include "Delay.h"
#include "motor.h"
#include "app.h"
#include "main.h"


/*====================================
函数名	：IR_Avoid
参数	：无
返回值	：无
描述	：智能小车红外避障
====================================*/
//void IR_Avoid()
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
函数名	：IR_Tracking
参数	：无
返回值	：无
描述	：智能小车红外循迹
====================================*/
void IR_Tracking()
{
		/*1为识别到黑线*/
	if((TrackSensorLeft == 1) && (TrackSensorRight == 1))
	{	
		SmartCarForward(LeftSpeed, RightSpeed);//前进	
	}else if((TrackSensorLeft == 0) && (TrackSensorRight == 1))
	{
		SmartCarRight(255, RightSpeed);//右转
	}else if((TrackSensorLeft == 1) && (TrackSensorRight == 0))
	{

		SmartCarLeft(LeftSpeed, 255);//左转	
	}
}
