#include "common.h"
#include "include.h"

void servo_init()
{
	ftm_pwm_init(SERVO_FTM, SERVO_CH,SERVO_HZ,INIT_DUTY);
}


/*void set_servo_angle (int angle)
{
	int servo_out=(int )(92+angle/900.0*120);
	ftm_pwm_duty(SERVO_FTM,SERVO_CH,servo_out);
}*/

void set_servo_angle (int angle)
{
	float servo_out = (float ) (LEFT_BOUND_DUTY - ((float)(LEFT_BOUND_DUTY - RIGHT_BOUND_DUTY) * angle / 10000));
	ftm_pwm_duty(SERVO_FTM,SERVO_CH,(int)servo_out);
}