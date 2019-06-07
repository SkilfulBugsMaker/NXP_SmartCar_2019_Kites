#include "common.h"
#include "include.h"


//初始化电机四个通道，对于电机的调速只涉及到左右前向通道，后向通道的占空比保持不变
void motor_init(void)
{
    /*******************************************************************************/
    //设置后向基准占空比
    ftm_pwm_init(MOTOR_FTM, R_MOTOR_CH_B, MOTOR_HZ, R_MOTOR_DUTY_B);
    ftm_pwm_init(MOTOR_FTM, L_MOTOR_CH_B, MOTOR_HZ, L_MOTOR_DUTY_B);
    /*******************************************************************************/

    /*******************************************************************************/
    //设置前向初始占空比
    ftm_pwm_init(MOTOR_FTM, L_MOTOR_CH_F, MOTOR_HZ, L_MOTOR_INIT_DUTY_F);
    ftm_pwm_init(MOTOR_FTM, R_MOTOR_CH_F, MOTOR_HZ, R_MOTOR_INIT_DUTY_F);
    /*******************************************************************************/
}


void set_left_speed(int l_speed)
{
    float dest = L_MOTOR_MIN_DUTY_F + ((float)(L_MOTOR_MAX_DUTY_F - L_MOTOR_MIN_DUTY_F)/MOTOR*l_speed);
    ftm_pwm_duty(MOTOR_FTM,L_MOTOR_CH_F,(int)dest);
}


void set_right_speed(int r_speed)
{
    float dest = R_MOTOR_MIN_DUTY_F + ((float)(R_MOTOR_MAX_DUTY_F - R_MOTOR_MIN_DUTY_F)/MOTOR*r_speed);
    ftm_pwm_duty(MOTOR_FTM,R_MOTOR_CH_F,(int)dest);
}


