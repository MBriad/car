#include "config.h"
#include "timer_ISR.h"
#include "ultrasonic.h"
#include "Delay.h"

/*超声波触发*/
void TrigUltrasonic()
{
	TrigPin = 0; //超声波模块Trig	控制端
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TrigPin = 1; //超声波模块Trig	控制端
	Delay15us();
	TrigPin = 0; //超声波模块Trig	控制端
}
/*====================================
函数名	：GetDistance
参数	：无
返回值	：获取距离单位毫米
描述	：超声波测距
通过发射信号到收到回响信号的时间测试距离
单片机晶振11.0592Mhz
注意测距周期为60ms以上
====================================*/
unsigned int GetDistance()
{
	unsigned int Distance = 0;	//超声波距离
	unsigned int  Time=0;		//用于存放定时器时间值
	TrigUltrasonic();	//超声波触发
	while(!EchoPin);  	//判断回响信号是否为低电平
	Timer1On;			//启动定时器1
	while(EchoPin);		//等待收到回响信号
	Timer1Off;			//关闭定时器1
	Time=TH1*256+TL1;	//读取时间
	TH1=0;
	TL1=0;				//清空定时器
    Distance = (float)(Time*1.085)*0.17;//算出来是MM
	return(Distance);//返回距离				
}
