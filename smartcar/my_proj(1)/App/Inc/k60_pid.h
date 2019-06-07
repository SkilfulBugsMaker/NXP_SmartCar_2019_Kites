#ifndef K60_PID_H_INCLUDED
#define K60_PID_H_INCLUDED

typedef struct
{
    float kp,ki,kd;
    float err_1,err_0;
    float real,dest,output;
    float err_acc;
}PID;

//初始化PID各项参数
void PID_init(PID *p, const float kp, const float ki, const float kd);

//计算pid_OUTPUT,这是位置式PID
void PID_compute_1(PID *p);

//计算PID_OUTPUT,这是增量式PID
void PID_compute_2(PID *p);

//模糊PID
void PID_compute_3(PID *p);

void PID_compute_4(PID *p);

#endif  // K60_PID_H_INCLUDED