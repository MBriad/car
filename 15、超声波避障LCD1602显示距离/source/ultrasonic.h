#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

void TrigUltrasonic();				//触发超声波测距
unsigned int GetDistance();	//超声波测距，返回：距离，单位：毫米

#endif