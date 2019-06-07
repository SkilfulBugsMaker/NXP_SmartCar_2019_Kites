#include "common.h"
#include "include.h"


void servo_init()
{
	ftm_pwm_init(SERVO_FTM, SERVO_CH,SERVO_HZ,INIT_DUTY);
}


void set_servo_angle (int angle)
{
	float servo_out = (float )(LEFT_BOUND_DUTY - ((float)(LEFT_BOUND_DUTY - RIGHT_BOUND_DUTY)/SERVO*angle));
	ftm_pwm_duty(SERVO_FTM,SERVO_CH,(int)servo_out);
}