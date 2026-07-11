#include "config.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "Delay.h"
#include "motor.h"
#include "Servo.h"
#include "app.h"
#include "main.h"

bit Timer1Overflow;	//计数器1溢出标志位
uchar code ASCII[13] = "0123456789";
uchar disbuff[4]={0,0,0,0};//用于分别存放距离的值米，厘米，毫米
uint LeftDistance = 0, RightDistance = 0, FrontDistance = 0; //云台测距距离缓存
uint DistBuf[5] = {0};//distance data buffer

/*====================================
函数名	：DispDistance(unsigned long Val)
参数	：距离
返回值	：无
描述	：LCD1602显示距离
显示距离单位：毫米
====================================*/
void DispDistance(unsigned int Val)
{
	if((Val >= 5000) || (Timer1Overflow == 1))//超出测量范围
	{
		Timer1Overflow = 0; //清除定时器溢出标志位
		LCD1602_Dis_Str(0, 1, "!!! Out of range"); //LCD1602显示字符串	
	}
	else
	{
		/*显示距离单位毫米*/
		disbuff[0]=Val/1000; //距离数值千位
		disbuff[1]=Val%1000/100;//距离数值百位
		disbuff[2]=Val%100/10;//距离数值十位
		disbuff[3]=Val%10; //距离数值个位
		LCD1602_Dis_Str(0, 1, "Distance:0000 MM"); //显示：Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 1,  ASCII[disbuff[0]]); //显示千位
	    LCD1602_Dis_OneChar(10, 1, ASCII[disbuff[1]]);	
	    LCD1602_Dis_OneChar(11, 1, ASCII[disbuff[2]]);	
	    LCD1602_Dis_OneChar(12, 1, ASCII[disbuff[3]]); 				
	}		
}
//冒泡排序
void bubble(unsigned int *a,unsigned char n) /*定义两个参数：数组首地址与数组大小*/
{
	unsigned int i,j,temp;	
	for(i = 0;i < n-1; i++)	
	{	
		for(j = i + 1; j < n; j++) /*注意循环的上下限*/
		{
			if(a[i] > a[j])
			{
				temp = a[i];		
				a[i] = a[j];		
				a[j] = temp;			
			}
		}
	}

}
/*====================================
函数名	：RefreshDistance
参数	：无
返回值	：经过冒泡排序后的距离
描述	：经过5次测距，去除最大值和最小值，取中间3次平均值
距离单位：毫米
====================================*/
unsigned int RefreshDistance()
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf[num] = GetDistance();
		Delay1ms(60);//测距周期不低于60毫秒	
	}
	bubble(DistBuf, 5);//
	Dist = (DistBuf[1]+DistBuf[2]+DistBuf[3])/3; //去掉最大和最小取中间平均值
	return(Dist);
}
/*红外避障*/
void IR_Avoid()
{
	if(UAvoidSensorLeft == 0)
	{
		SmartCarRight(LeftSpeed, RightSpeed);//右转	
	}else if(UAvoidSensorRight == 0)
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//左转		
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
void IR_Tracking()
{
		/*1为识别到黑线*/
	if((TrackSensorLeft == 1) && (TrackSensorRight == 1))
	{	
		SmartCarForward(LeftSpeed, RightSpeed);//前进	
	}else if((TrackSensorLeft == 0) && (TrackSensorRight == 1))
	{
		SmartCarRight(200, RightSpeed);//右转
	}else if((TrackSensorLeft == 1) && (TrackSensorRight == 0))
	{

		SmartCarLeft(LeftSpeed, 200);//左转	
	}
}
/*====================================
函数名	：TrackingAvoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车黑线循迹加避障，当出现障碍物时，智能小车停车等待
障碍物移除后智能小车继续循迹
距离单位：毫米
====================================*/
void TrackingAvoid(uint val)
{
	uint Dis;//距离暂存变量
	Dis = GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < val)
	{	
		do{
		 	BUZZER_on;//开启蜂鸣器
			SmartCarStops();	//停车
			Delay1ms(60);
			Dis = GetDistance();//获取超声波测距距离,单位：毫米
		}while(Dis < val);
		BUZZER_off;//关闭蜂鸣器
		if((TrackSensorLeft == 0) && (TrackSensorRight == 0))
		{
			SmartCarBack(80, 80);//如果左右都出线了执行后退，回到黑线上
		}
	}
	else
	{
		for(Dis=0; Dis<1800; Dis++)//测距周期不低于60ms 这里借用Dis变量做循环
		{
			IR_Tracking();//红外循迹
		}
	}
}
/*====================================
函数名	：UltrasonicAvoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车超声波避障
距离单位：毫米
====================================*/
//void UltrasonicAvoid(uint val)
//{
//	uint Dis;//距离暂存变量
//	Dis = GetDistance();//获取超声波测距距离,单位：毫米
//	LCD1602_Dis_OneChar(0, 0, 'F');	//F表示前方距离
//	DispDistance(Dis);//LCD1602显示超声波测距距离
//	if(Dis < val)
//	{	
//		SmartCarStops();	//停车
//		Delay1ms(100);
//		SmartCarBack(LeftSpeed, RightSpeed);//后退
//		Delay1ms(50);//延时50ms
//		SmartCarLeftTurn(LeftSpeed, RightSpeed);//原地左转
//		Delay1ms(100);//延时100ms
//	}
//	else
//	{
//		for(Dis=0; Dis<1800; Dis++)//测距周期不低于60ms 这里借用Dis变量做循环
//		{
//			IR_Avoid();//红外避障
//		}
//	}
//
//}
/*====================================
函数名	：PTZ_Avoid
参数	：无
返回值	：小车车头前方距离
描述	：智能小车舵机云台避障
距离单位：毫米
====================================*/
void PTZ_Avoid()
{
	uint Dis;//距离暂存变量
	Dis = GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < 300)
	{
		LCD1602_Dis_OneChar(0, 0, 'D');
		DispDistance(Dis);//LCD1602显示超声波测距距离	
		SmartCarStops();	//停车
		Delay1ms(100);

		/*舵机左转测距*/
		ServoLeft();
		LeftDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'L');
		DispDistance(LeftDistance);//LCD1602显示超声波测距距离
		Delay1ms(100);

		/*舵机右转测距*/
		ServoRight();
		RightDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'R');
		DispDistance(RightDistance);//LCD1602显示超声波测距距离
		Delay1ms(100);

		/*舵机正前方测距*/
		ServoFront();
		FrontDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'F');
		DispDistance(FrontDistance);//LCD1602显示超声波测距距离
		Delay1ms(100);
		if((FrontDistance<100) && (LeftDistance<100) && (RightDistance<100))
		{
			do{
				SmartCarLeftTurn(255, 255);//原地左转
				Delay1ms(50);
				/*舵机正前方测距*/
				ServoFront();
				Dis = RefreshDistance();
				LCD1602_Dis_OneChar(0, 0, 'D');
				DispDistance(Dis);//LCD1602显示超声波测距距离
				Delay1ms(100);		
			}while(Dis < 200);
		}else if(LeftDistance > RightDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'L');
			DispDistance(LeftDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarLeftTurn(255, 255);//原地左转
			Delay1ms(80);		
		}else if(RightDistance > LeftDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'R');
			DispDistance(RightDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarRightTurn(255, 255);//原地右转
			Delay1ms(80);	
		}else if((FrontDistance>LeftDistance) && (FrontDistance>RightDistance))
		{
			LCD1602_Dis_OneChar(0, 0, 'F');
			DispDistance(FrontDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarForward(LeftSpeed, RightSpeed);//前进
		}		
	}
	else
	{
		for(Dis=0; Dis<1800; Dis++)//测距周期不低于60ms 这里借用Dis变量做循环
		{
			IR_Avoid();//红外避障
		}
	}			
}

