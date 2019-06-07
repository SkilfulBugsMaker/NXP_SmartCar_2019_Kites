/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.2
 * @date       2014-11-03
 */

#include "common.h"
#include "include.h"


#define AHEAD 8000.0
/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       FTM PWM 电机驱动测试
 */
void pit_5ms(void);
void FTM2_INPUT_IRQHandler(void);
void PORTA_IRQHandler();
void DMA0_IRQHandler();
PID c_PID;
CAMERA_ERR c_err;
int Lee,Ree;
float real_1;
float err;

uint8 f_midline[CAMERA_H];


volatile unsigned int countL=0,countR=0;
void main(void)
{
    
    uint8 imgbuff[CAMERA_SIZE];                             
    uint8 img[CAMERA_H*CAMERA_W];
    uint8 midline[CAMERA_H];//中心线
    uint8 imgcompress[CAMERA_SIZE];//重压缩后的二值化图像
    
    pit_init_ms(PIT0, 5);//初始化PIT0，定时时间为： 5ms
    set_vector_handler(PIT0_VECTORn ,pit_5ms);//设置PIT0的中断服务函数为 pit_5ms
    enable_irq (PIT0_IRQn);//使能PIT0中断
    
    
    //ftm_input_init(FTM2, FTM_CH1, FTM_Falling,FTM_PS_2);     //初始化FTM输入捕捉模式，下降沿捕捉(FTM0_CH6 为 PTD6)
    //ftm_input_init(FTM2, FTM_CH0, FTM_Falling, FTM_PS_2);
    //set_vector_handler(FTM2_VECTORn ,FTM2_INPUT_IRQHandler);    //设置FTM0的中断服务函数为 FTM0_INPUT_IRQHandler
    //enable_irq (FTM2_IRQn);
    
   
    
    
    
    
    PID_init (&c_PID,9000,0,8300);
    
    adc_init(ADC1_SE9);              //ADC初始化
    adc_init(ADC1_SE8);
    
    servo_init();
    //ftm_pwm_duty(SERVO_FTM,SERVO_CH,1140);

    motor_init();
    set_left_speed(1000);
    set_right_speed(1000);
    
    
    
    
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //设置DMA0的中断服务函数为 DMA0_IRQHandler
    camera_init(imgbuff); 
    while(1)
    {
       //获取图像
        camera_get_img();                                   //摄像头获取图像

        img_extract(img, imgbuff,CAMERA_SIZE);                  //解压图像
        
        Find_Midline(img,midline);
        MakeUpWhiteIslands_W(img,midline);
        Find_Midline(img,midline);
        final_midline(midline,f_midline);
        
        //Paint_Midline(img,midline);
        //img_compress(imgcompress,img,CAMERA_W * CAMERA_H);
        //vcan_sendimg(imgcompress, CAMERA_SIZE); 
    }
    
    
  
}


void pit_5ms(void)
{
    calc_camera_err(f_midline, &c_err);
    
    Ree = adc_once(ADC1_SE9, ADC_8bit);
    Lee = adc_once(ADC1_SE8, ADC_8bit);
    real_1 = (float)(Lee-Ree)/(Lee+Ree);
    
    err=0.7*c_err.err_2+0.05*real_1;
    
    
    
    c_PID.dest=0;
    c_PID.real=err;
    PID_compute_1(&c_PID);
    float out = c_PID.output+5000;
    if (out<0)
        out=0;
    if (out>SERVO)
        out=SERVO;
    set_servo_angle ((int)out);
    
    
    float l_speed,r_speed;
    if (err<0.05){
        l_speed=AHEAD;
        r_speed=AHEAD;
    }
    else{
        l_speed = AHEAD - 11000*fabs(err) + 5000*fabs(err);
        r_speed = 1.02*(AHEAD - 11000*fabs(err)- 5000*fabs(err));
    }
    set_left_speed((int)l_speed);
    set_right_speed((int)r_speed);
    
    
    //printf ("%d,%d,%f,%f\n",countL,countR,lm_PID.output,rm_PID.output);
    
    countL=0;
    countR=0;
    
    
    
    
    PIT_Flag_Clear(PIT0);  //清中断标志位
}


/*void FTM2_INPUT_IRQHandler(void)
{
    uint8 s = FTM2_STATUS;          //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    uint8 CHn;
    
    FTM2_STATUS = 0x00;
    CHn = 0;
    if( s & (1 << CHn) )
    {
        countL++;
    }
    
    CHn = 1;
    if(s & (1<<CHn))
    {
        countR++;
    }
}
*/

void PORTA_IRQHandler()
{
    uint8  n = 0;    //引脚号
    uint32 flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if 0             //鹰眼直接全速采集，不需要行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif
}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}