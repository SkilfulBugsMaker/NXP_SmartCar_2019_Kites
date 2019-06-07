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
 * @version    v5.3
 * @date       2015-04-07
 */

#include "common.h"
#include "include.h"
#include "camera.h"
#include "math.h"

uint8 midline[CAMERA_H];//中心线
uint8 imgcompress[CAMERA_SIZE];//重压缩后的二值化图像
uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_W*CAMERA_H];                           //由于鹰眼摄像头是一字节8个像素，因而需要解压为 1字节1个像素，方便处理
                    //假如需要二维数组，只需要改成 uint8 img[CAMERA_H][CAMERA_W];
                    //imgbuff是采集的缓冲区，img是解压后的缓冲区。imgbuff用于采集图像，img用于图像处理.

//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();


/*!
 *  @brief      main函数
 *  @since      v5.3
 *  @note       山外 DMA 采集摄像头 实验
                注意，此例程 bus频率设为100MHz(50MHz bus频率会太慢而导致没法及时采集图像)

                此例程使用的上位机为【山外多功能调试助手】
                具体资料请参考：山外多功能调试助手资料专辑
                                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=27
 */
void  main(void)
{
    ftm_pwm_init(FTM0,FTM_CH2,10000,40);
    ftm_pwm_duty(FTM0,FTM_CH2,40);
    
    //初始化摄像头
    camera_init(imgbuff);                                  //这里设定  imgbuff 为采集缓冲区！！！！！！

    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //设置DMA0的中断服务函数为 DMA0_IRQHandler

    while(1)
    {
        //获取图像
        camera_get_img();                                   //摄像头获取图像

        /***********  提供两种方式可供用户自行选择【二值化模式】、【灰度模式】  ************/
        /***  强调一点：所谓的灰度模式，实际上只有2个像素值，即已经二值化好的灰度模式。  ***/

#if 0       //不解压，直接发送二值化图像到上位机。上位机选择【二值化模式】

        //发送图像到上位机
        vcan_sendimg(imgbuff, CAMERA_SIZE);                  //发送到上位机

#else     //解压，生成只有2个像素值的灰度图像到上位机。上位机选择【灰度模式】

        img_extract(img, imgbuff,CAMERA_SIZE);                  //解压图像
        
        Find_Midline(img,midline);
        MakeUpWhiteIslands_W(img,midline);
        Find_Midline(img,midline);
        Paint_Midline(img,midline);
        
        img_compress(imgcompress,img,CAMERA_W * CAMERA_H);
        vcan_sendimg(imgcompress, CAMERA_SIZE); 
        //vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //发送到上位机
#endif
    }
}

/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
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
#if 1             //鹰眼直接全速采集，不需要行中断
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