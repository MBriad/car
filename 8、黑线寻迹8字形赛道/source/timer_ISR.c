#include "config.h"
#include "timer_ISR.h"
#include "motor.h"

uchar PWM_T;//PWW周期
/*=================================================
*函数名称：IntRegInit
*函数功能：中断寄存器初始化
*调用：
*输入：
=================================================*/
void IntRegInit()
{
	ET0 = 1;//允许定时器0中断
	EA	= 1;//总中断允许	
}
/*定时器0初始化*/
void Timer0Init(void)		//100微秒@11.0592MHz
{
	TMOD |= 0x02;//定时器0，8位自动重装模块
	TH0 = 0xA4;
	TL0 = 0xA4;//100US中断一次
	TR0 = 1;//启动定时器0
}

/* Timer0 interrupt routine */
void tm0_isr() interrupt 1 using 1
{
	if(PWM_T == 255)//PWW周期		//频率F=1000000/T0溢出时间*255
	{
		PWM_T = 0;
	}
	if(RightMotorSpeed >= PWM_T)
	{
		RightMotor_EN = 1;	//使能右马达
	}
	if(LeftMotorSpeed >= PWM_T)
	{
	 	LeftMotor_EN  = 1;  //使能左马达
	}		
	if(LeftMotorSpeed < PWM_T)
	{
	 	LeftMotor_EN  = 0;  //禁用左马达
	}		
	if(RightMotorSpeed < PWM_T)
	{
		RightMotor_EN = 0;	//禁用右马达
	}
	PWM_T++;//PWW周期控制变量	
}
