#include "common.h"
#include "include.h"

/********************************************/
//test1
/*void main()
{
    servo_init();
    DELAY_MS(1000);
    ftm_pwm_duty(SERVO_FTM,SERVO_CH,1210);
    DELAY_MS(1000);
    int i=0;
    while (1)
    {
      for (i=1200;i<=1630;i+=10)
      {  
          ftm_pwm_duty(SERVO_FTM,SERVO_CH,i);
          DELAY_MS(10);
      }
      for (i=1630;i>=1200;i-=10)
      {  
          ftm_pwm_duty(SERVO_FTM,SERVO_CH,i);
          DELAY_MS(10);
      }
    }
    DELAY_MS(500);  
}*/

/********************************************/

/********************************************/
//test2
void main()
{
    servo_init();
    DELAY_MS(1000);
    ftm_pwm_duty(SERVO_FTM,SERVO_CH,1210);
    DELAY_MS(1000);
    int i=0;
    while (1)
    {
      for (i=0;i<=1000;i+=10)
      {  
          set_servo_angle (i);
          DELAY_MS(10);
      }
      for (i=1000;i>=0;i-=10)
      {  
          set_servo_angle (i);
          DELAY_MS(10);
      }
    }
    DELAY_MS(500);  
}

/********************************************/
