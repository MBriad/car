#include "config.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "Delay.h"
#include "motor.h"
#include "Servo.h"
#include "app.h"
#include "main.h"

bit Timer1Overflow;
bit Timer2Overflow;

uchar code ASCII[13] = "0123456789";
uchar disbuff[4] = {0, 0, 0, 0};
uint DistBuf[5] = {0};

/* Direction labels for LCD */
uchar code *dirNames[5] = {
	"Dir: Front  ",
	"Dir: Left   ",
	"Dir: Right  ",
	"Dir: Left45 ",
	"Dir: Right45"};

/*====================================
  LFSR pseudo-random number generator
  Polynomial: x^8 + x^4 + x^3 + x^2 + 1
====================================*/
static unsigned char lfsr;

void InitRandom(void)
{
	lfsr = TH1 ^ TL1;
	if (lfsr == 0)
		lfsr = 0xAA;
}

unsigned char RandomByte(void)
{
	unsigned char fb;
	fb = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 4)) & 1;
	lfsr = (lfsr >> 1) | (fb << 7);
	return lfsr;
}

/*====================================
  LCD1602 display distance
  Unit: mm
====================================*/
void DispDistance(unsigned int Val)
{
	if ((Val >= 5000) || (Timer1Overflow == 1))
	{
		Timer1Overflow = 0;
		LCD1602_Dis_Str(0, 0, "!!! Out of range");
	}
	else
	{
		disbuff[0] = Val / 1000;
		disbuff[1] = Val % 1000 / 100;
		disbuff[2] = Val % 100 / 10;
		disbuff[3] = Val % 10;
		LCD1602_Dis_Str(0, 0, "Distance:0000 MM");
		LCD1602_Dis_OneChar(9, 0, ASCII[disbuff[0]]);
		LCD1602_Dis_OneChar(10, 0, ASCII[disbuff[1]]);
		LCD1602_Dis_OneChar(11, 0, ASCII[disbuff[2]]);
		LCD1602_Dis_OneChar(12, 0, ASCII[disbuff[3]]);
	}
}

/*====================================
  Bubble sort (ascending)
====================================*/
void bubble(unsigned int *a, unsigned char n)
{
	unsigned int i, j, temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

/*====================================
  5-sample filtered distance
  Drop max & min, average middle 3
====================================*/
unsigned int RefreshDistance()
{
	uchar num;
	uint Dist;
	for (num = 0; num < 5; num++)
	{
		DistBuf[num] = GetDistance();
		Delay1ms(60);
	}
	bubble(DistBuf, 5);
	Dist = (DistBuf[1] + DistBuf[2] + DistBuf[3]) / 3;
	return (Dist);
}

/*====================================
  Pick 2 distinct directions from 5
====================================*/
void PickTwoDirections(unsigned char *d1, unsigned char *d2)
{
	*d1 = RandomByte() % 5;
	do
	{
		*d2 = RandomByte() % 5;
	} while (*d2 == *d1);
}

/*====================================
  Map direction index to servo angle
  0=Front, 1=Left(+90), 2=Right(-90),
  3=Left45(+45), 4=Right45(-45)
====================================*/
void SetServo(unsigned char dir)
{
	switch (dir)
	{
	case 0:
		ServoFront();
		break;
	case 1:
		ServoLeft();
		break;
	case 2:
		ServoRight();
		break;
	case 3:
		ServoLeft45();
		break;
	case 4:
		ServoRight45();
		break;
	}
}

/*====================================
  Measure distance in one direction
====================================*/
unsigned int MeasureDirection(unsigned char dir)
{
	unsigned int dist;
	SetServo(dir);
	Delay1ms(300);
	LCD1602_Dis_Str(0, 1, dirNames[dir]);
	dist = RefreshDistance();
	DispDistance(dist);
	return dist;
}

/*====================================
  Buzzer alert, turn car, then ram
====================================*/
void RamTarget(unsigned char dir)
{
	LCD1602_Clear_Screen();
	LCD1602_Dis_Str(0, 0, "Target locked!");
	BUZZER_on;
	Delay1ms(500);
	BUZZER_off;
	SetServo(dir);
	Delay1ms(300);

	/* Turn car body to face target direction */
	switch (dir)
	{
	case 0: /* Front */
		break;
	case 1: /* Left  +90 */
		SmartCarLeftTurn(255, 255);
		Delay1ms(200);
		break;
	case 2: /* Right -90 */
		SmartCarRightTurn(255, 255);
		Delay1ms(200);
		break;
	case 3: /* Left45 +45 */
		SmartCarLeftTurn(255, 255);
		Delay1ms(180);
		break;
	case 4: /* Right45 -45 */
		SmartCarRightTurn(255, 255);
		Delay1ms(180);
		break;
	}
	SmartCarStops();
	Delay1ms(200);

	LCD1602_Dis_Str(0, 1, "RAMMING!!!     ");
	SmartCarForward(255, 255);
	Delay1ms(3000);
	SmartCarStops();
}

/*====================================
  Top-level assessment flow:
  Init PRNG -> Pick 2 dirs -> Measure
  -> Find nearest -> Ram it
====================================*/
void AssessmentRun(void)
{
	unsigned char dir1, dir2;
	unsigned int dist1, dist2;
	unsigned char bestDir;

	InitRandom();
	PickTwoDirections(&dir1, &dir2);

	LCD1602_Dis_Str(0, 0, "Measuring...   ");
	dist1 = MeasureDirection(dir1);
	Delay1ms(500);

	dist2 = MeasureDirection(dir2);
	Delay1ms(500);

	bestDir = (dist2 < dist1) ? dir2 : dir1;
	RamTarget(bestDir);
}
