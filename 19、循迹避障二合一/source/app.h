#ifndef _APP_H
#define _APP_H

extern bit Timer1Overflow;	//计数器1溢出标志位
void DispDistance(unsigned int Val);//LCD1602显示超声波测距距离
void bubble(unsigned int *a, unsigned char n);
unsigned int RefreshDistance();
void PTZ_Avoid();
void IR_Avoid();
void UltrasonicAvoid(uint val);//超声波避障
void IR_Tracking(); //黑线循迹
void TrackingAvoid(uint val);//循迹避障二合一
#endif