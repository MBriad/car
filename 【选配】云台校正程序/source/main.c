#define  _MAIN_C
#include "config.h"
#include "Delay.h"
#include "servo.h"
#include "main.h"

void main()
{
	delay(1000); //延时1s
	ServoFront();//舵机云台朝向正前方
	while(1);
}