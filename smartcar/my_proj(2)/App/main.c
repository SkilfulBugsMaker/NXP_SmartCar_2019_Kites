/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-11-03
 */

#include "common.h"
#include "include.h"


#define AHEAD 8000.0
/*!
 *  @brief      main����
 *  @since      v5.2
 *  @note       FTM PWM �����������
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
    uint8 midline[CAMERA_H];//������
    uint8 imgcompress[CAMERA_SIZE];//��ѹ����Ķ�ֵ��ͼ��
    
    pit_init_ms(PIT0, 5);//��ʼ��PIT0����ʱʱ��Ϊ�� 5ms
    set_vector_handler(PIT0_VECTORn ,pit_5ms);//����PIT0���жϷ�����Ϊ pit_5ms
    enable_irq (PIT0_IRQn);//ʹ��PIT0�ж�
    
    
    //ftm_input_init(FTM2, FTM_CH1, FTM_Falling,FTM_PS_2);     //��ʼ��FTM���벶׽ģʽ���½��ز�׽(FTM0_CH6 Ϊ PTD6)
    //ftm_input_init(FTM2, FTM_CH0, FTM_Falling, FTM_PS_2);
    //set_vector_handler(FTM2_VECTORn ,FTM2_INPUT_IRQHandler);    //����FTM0���жϷ�����Ϊ FTM0_INPUT_IRQHandler
    //enable_irq (FTM2_IRQn);
    
   
    
    
    
    
    PID_init (&c_PID,9000,0,8300);
    
    adc_init(ADC1_SE9);              //ADC��ʼ��
    adc_init(ADC1_SE8);
    
    servo_init();
    //ftm_pwm_duty(SERVO_FTM,SERVO_CH,1140);

    motor_init();
    set_left_speed(1000);
    set_right_speed(1000);
    
    
    
    
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //����DMA0���жϷ�����Ϊ DMA0_IRQHandler
    camera_init(imgbuff); 
    while(1)
    {
       //��ȡͼ��
        camera_get_img();                                   //����ͷ��ȡͼ��

        img_extract(img, imgbuff,CAMERA_SIZE);                  //��ѹͼ��
        
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
    
    
    
    
    PIT_Flag_Clear(PIT0);  //���жϱ�־λ
}


/*void FTM2_INPUT_IRQHandler(void)
{
    uint8 s = FTM2_STATUS;          //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
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
    uint8  n = 0;    //���ź�
    uint32 flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if 0             //ӥ��ֱ��ȫ�ٲɼ�������Ҫ���ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}