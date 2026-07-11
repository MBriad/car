#define  _MAIN_C
#include "config.h"
#include "Delay.h"
#include "servo.h"
#include "main.h"

void main()
{
	ServoFront();//舵机云台朝向正前方
	delay(1000); //延时1s
	while(1)
	{
		ServoLeft();//云台向左转动
		ServoFront();//云台向正前方转动
		ServoRight();//云台向右转动
		ServoFront();//云台向正前方转动
	}
}