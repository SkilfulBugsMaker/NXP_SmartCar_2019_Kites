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

/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       FTM PWM 电机驱动测试
 */
void main(void)
{
    uint8 i = 0;
    printf("\n*****FTM PWM 电机测试*****\n");

    ftm_pwm_init(FTM0, FTM_CH0,500,0); //R1        //初始化 FTM PWM ，使用 FTM0_CH3，频率为10k ，占空比为 100 / FTM0_PRECISON
    ftm_pwm_init(FTM0, FTM_CH2,500,25); //R2
    ftm_pwm_init(FTM0, FTM_CH1,500,25); //L1
    ftm_pwm_init(FTM0, FTM_CH3,500,0); //L2
    DELAY_MS(1000);
    
    
    DELAY_MS(1000);                                            // FTM0_PRECISON 配置 为 100 ，即占空比 为 100%
                                                    // port_cfg.h 里 配置 FTM0_CH3 对应为 PTA6
   // gpio_init(PTD15,GPO,0);                         // 使能端 输入为 0

    //山外的电机驱动模块，经过 MOS 管 反相隔离。
    //K60 输出 PWM 为 100% ，实际接入 电机驱动就是 0%
    //K60 输出 使能端 为 低电平，实际接入 电机驱动 使能端就是 高电平
      
            //ftm_pwm_duty(FTM1,FTM_CH0,90);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
            //DELAY_MS(1000);
       
    while(1)
    {
        for(i= 0;i<=50;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH0,i);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
            ftm_pwm_duty(FTM0,FTM_CH3,i);
            DELAY_MS(100);
        }
        
        for(i= 50;i>=2;i-=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH0,i);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
            ftm_pwm_duty(FTM0,FTM_CH3,i);
            DELAY_MS(100);
        }
        
        /*for(i= 0;i<=40;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH2,i);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
            DELAY_MS(15);
        }
        
        for(i= 0;i<=40;i+=2)
        {
            ftm_pwm_duty(FTM0,FTM_CH3,i);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
            DELAY_MS(15);
        }*/
        
       // for(i= 100;i>=50;i-=10)
        //{
       //     ftm_pwm_duty(FTM1,FTM_CH0,i);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
       //     DELAY_MS(500);
       // }
      //ftm_pwm_duty(FTM1,FTM_CH0,50);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
         // DELAY_MS(200);
      //ftm_pwm_duty(FTM1,FTM_CH0,95);       //改变 占空比 ，K60 输出 PWM 占空比 逐渐增大，电机逐渐 降速
           //DELAY_MS(200);
      
    }
}
