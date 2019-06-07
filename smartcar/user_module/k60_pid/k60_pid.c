#include "include.h"
#include "common.h"


//初始化PID
void PID_init(PID *p, float kp, float ki, float kd)
{
    p->kp = kp;
    p->ki = ki;
    p->kd = kd;
    p->err_1 = 0.0;
    p->err_0 = 0.0;
    p->output = 0.0;
    p->err_acc = 0.0;
    p->real = 0.0;
    p->dest = 0.0
}

//计算位置式PID输出，简单
void PID_compute(PID *p)
{
    float err = p->real - p->dest;
    (p->output) = p->dest+(p->kp)*err + (p->ki)*(p->err_acc) + (p->kd)*(err-(p->err_1));
    (p->err_acc) += err;
    (p->err_1) = err;
}

//计算增量式PID输出，优点，更加稳定
void PID_compute_2(PID *p)
{
    float err = p->real - p->dest;
    float delta = (p->kp)*(err - p->err_1) + (p->ki)*err + (p->kd)*(err-2*(p->err_1)+(p->err_0));
    p->err_0 = p->err_1;
    p->err_1 = err;
    p->output = p->real + delta;
}


//计算模糊PID输出。
void PID_compute_3(PID *p)
{
    float err = p->real - p->dest;
    float err_c = err - p->err_1;
}
