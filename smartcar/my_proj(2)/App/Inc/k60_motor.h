#ifndef K60_MOTOR_H_INCLUDED
#define K60_MOTOR_H_INCLUDED

//请将 FTM0 方波占空比精度改为10000u
//精度定义在MK60_FTM.h

#define MOTOR 10000u


//左右电机FTM
#define MOTOR_FTM FTM0

//左右电机的PWM频率
#define MOTOR_HZ 19000

//左右电机共计4个通道，分为左前，左后，右前，右后
#define L_MOTOR_CH_F FTM_CH1
#define L_MOTOR_CH_B FTM_CH3
#define R_MOTOR_CH_F FTM_CH2
#define R_MOTOR_CH_B FTM_CH0

//后向通道的基准占空比
#define L_MOTOR_DUTY_B 2000
#define R_MOTOR_DUTY_B 2000

//前向通道的初始化占空比
#define L_MOTOR_INIT_DUTY_F 2000
#define R_MOTOR_INIT_DUTY_F 2000



//前向通道的最大占空比
#define R_MOTOR_MAX_DUTY_F 8000
#define L_MOTOR_MAX_DUTY_F 8000

//前向通道的最小占空比，在没有倒车需求的时候该值等于后向通道基准占空比
#define R_MOTOR_MIN_DUTY_F 2000
#define L_MOTOR_MIN_DUTY_F 2000



//左右电机初始化函数
void motor_init(void);


//设置左、右电机的速度
//输入电机的l_speed和r_speed范围在0-10000
//映射到MIN_DUTY 到 MAX_DUTY
void set_left_speed(int l_speed);
void set_right_speed(int r_speed);




#endif // K60_MOTOR_H_INCLUDED
