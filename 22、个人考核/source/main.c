/*
 * Module 22: Personal Assessment
 * MCU: STC89C52, 11.0592MHz
 * Platform: QX-MCS51 + QX-A51 Smart Car
 * Compiler: Keil C51
 * Description: Randomly pick 2 of 5 directions, servo to each,
 *              measure distance, buzzer alert, ram nearest target.
 * Entry point: AssessmentRun() in app.c
 */

#define _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "app.h"
#include "Servo.h"
#include "main.h"

uchar LeftSpeed, RightSpeed;

void keyscan()
{
	for (;;)
	{
		if (KEY_S2 == 0)
		{
			Delay1ms(5);
			if (KEY_S2 == 0)
			{
				while (!KEY_S2)
					;
				BUZZER_on;
				Delay1ms(200);
				BUZZER_off;
				break;
			}
		}
	}
}

void main()
{
//	LeftSpeed  = 150;
//	RightSpeed = 150;
	IntRegInit();                                // Init interrupt registers
	Timer0Init();                                // Init PWM speed control
	Timer1Init();                                // Init Timer1
	Init_LCD1602();                              // Init LCD1602
	ServoFront();                                // Servo to front
	LCD1602_Dis_Str(0, 0, "Please press the");   // Prompt message
	LCD1602_Dis_Str(0, 1, "S2 to start");        // Prompt message
	keyscan();                                   // Wait for S2 press
	LCD1602_Clear_Screen();                      // Clear LCD
	while (1)
	{
		AssessmentRun();
		SmartCarStops();
		while (1)
			;
	}
}
