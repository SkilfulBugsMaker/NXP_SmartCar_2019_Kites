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

/*!
 *  @brief      main����
 *  @since      v5.2
 *  @note       FTM PWM �����������
 */
void main(void)
{
    uint8 i = 0;
    printf("\n*****FTM PWM �������*****\n");

    ftm_pwm_init(FTM0, FTM_CH0,500,0); //R1        //��ʼ�� FTM PWM ��ʹ�� FTM0_CH3��Ƶ��Ϊ10k ��ռ�ձ�Ϊ 100 / FTM0_PRECISON
    ftm_pwm_init(FTM0, FTM_CH2,500,25); //R2
    ftm_pwm_init(FTM0, FTM_CH1,500,25); //L1
    ftm_pwm_init(FTM0, FTM_CH3,500,0); //L2
    DELAY_MS(1000);
    
    
    DELAY_MS(1000);                                            // FTM0_PRECISON ���� Ϊ 100 ����ռ�ձ� Ϊ 100%
                                                    // port_cfg.h �� ���� FTM0_CH3 ��ӦΪ PTA6
   // gpio_init(PTD15,GPO,0);                         // ʹ�ܶ� ����Ϊ 0

    //ɽ��ĵ������ģ�飬���� MOS �� ������롣
    //K60 ��� PWM Ϊ 100% ��ʵ�ʽ��� ����������� 0%
    //K60 ��� ʹ�ܶ� Ϊ �͵�ƽ��ʵ�ʽ��� ������� ʹ�ܶ˾��� �ߵ�ƽ
      
            //ftm_pwm_duty(FTM1,FTM_CH0,90);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
            //DELAY_MS(1000);
       
    while(1)
    {
        for(i= 0;i<=50;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH0,i);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
            ftm_pwm_duty(FTM0,FTM_CH3,i);
            DELAY_MS(100);
        }
        
        for(i= 50;i>=2;i-=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH0,i);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
            ftm_pwm_duty(FTM0,FTM_CH3,i);
            DELAY_MS(100);
        }
        
        /*for(i= 0;i<=40;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH2,i);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
            DELAY_MS(15);
        }
        
        for(i= 0;i<=40;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH3,i);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
            DELAY_MS(15);
        }*/
        
       // for(i= 100;i>=50;i-=10)
        //{
       //     ftm_pwm_duty(FTM1,FTM_CH0,i);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
       //     DELAY_MS(500);
       // }
      //ftm_pwm_duty(FTM1,FTM_CH0,50);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
         // DELAY_MS(200);
      //ftm_pwm_duty(FTM1,FTM_CH0,95);       //�ı� ռ�ձ� ��K60 ��� PWM ռ�ձ� �����󣬵���� ����
           //DELAY_MS(200);
      
    }
}
