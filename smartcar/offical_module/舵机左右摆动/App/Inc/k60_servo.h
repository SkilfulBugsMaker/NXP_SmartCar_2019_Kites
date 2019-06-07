#ifndef K60_SERVO_H_INCLUDED
#define K60_SERVO_H_INCLUDED

#define SERVO_FTM FTM1		//FTM
#define SERVO_CH FTM_CH0	//通道
#define	SERVO_HZ 100		//频率
#define INIT_DUTY 1410      //初始化占空比，这个角度不是很准

#define LEFT_BOUND_DUTY 1630 //左转边际占空比
#define RIGHT_BOUND_DUTY 1200 //右转边际占空比

/********************************************************/

//车模参数：
//在10000u的精度下，
//当达到1200的占空比的情况下达到右转极限，
//当达到1630的占空比的情况下达到左转极限，
//在void set_servo_angle (int angle)中，
//输入为0-1000的整形数值，
//其中0对应最左转，1000对应最右转。

/********************************************************/


//舵机初始化函数
void servo_init(void);


//输入舵机角度，对应0-900,请将PTA8对应的FTM方波占空比精度改为10000u
//精度定义在MK60_FTM.h
void set_servo_angle (int angle);

#endif // K60_SERVO_H_INCLUDED