#ifndef _APP_H
#define _APP_H

extern bit Timer1Overflow;	//计数器1溢出标志位
extern bit Timer2Overflow;
void DispDistance(unsigned int Val);//LCD1602显示超声波测距距离
void bubble(unsigned int *a, unsigned char n);
unsigned int RefreshDistance();
void PTZ_Avoid(uint val);
void IR_Avoid();
void My_DispDistance(unsigned int Val);
void My_TEST(void);
unsigned int My_RefreshDistance();
void My_TEST_2(void);



#endif