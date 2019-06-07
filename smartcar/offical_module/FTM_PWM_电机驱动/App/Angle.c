#include "Angle.h"
#include <math.h>
float GetAngle(float angle,float x_acc,float z_acc,float y_gyro){
    float angle_acc=0;
    x_acc -= 459;
    z_acc -= 714.5;
    y_gyro = - (500 * y_gyro/32768);

    angle_acc = atan(x_acc/z_acc*8366.5/8497)/3.1415926*180;
    angle += 0.98*y_gyro*0.005+0.02*(angle_acc-angle);
    
    return angle;
}