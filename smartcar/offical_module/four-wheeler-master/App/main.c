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
 * @version    v5.3
 * @date       2015-04-07
 */

#include "common.h"
#include "include.h"
#include "camera.h"
#include "math.h"

uint8 midline[CAMERA_H];//������
uint8 imgcompress[CAMERA_SIZE];//��ѹ����Ķ�ֵ��ͼ��
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
                    //������Ҫ��ά���飬ֻ��Ҫ�ĳ� uint8 img[CAMERA_H][CAMERA_W];
                    //imgbuff�ǲɼ��Ļ�������img�ǽ�ѹ��Ļ�������imgbuff���ڲɼ�ͼ��img����ͼ����.

//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();


/*!
 *  @brief      main����
 *  @since      v5.3
 *  @note       ɽ�� DMA �ɼ�����ͷ ʵ��
                ע�⣬������ busƵ����Ϊ100MHz(50MHz busƵ�ʻ�̫��������û����ʱ�ɼ�ͼ��)

                ������ʹ�õ���λ��Ϊ��ɽ��๦�ܵ������֡�
                ����������ο���ɽ��๦�ܵ�����������ר��
                                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=27
 */
void  main(void)
{
    ftm_pwm_init(FTM0,FTM_CH2,10000,40);
    ftm_pwm_duty(FTM0,FTM_CH2,40);
    
    //��ʼ������ͷ
    camera_init(imgbuff);                                  //�����趨  imgbuff Ϊ�ɼ�������������������

    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //����DMA0���жϷ�����Ϊ DMA0_IRQHandler

    while(1)
    {
        //��ȡͼ��
        camera_get_img();                                   //����ͷ��ȡͼ��

        /***********  �ṩ���ַ�ʽ�ɹ��û�����ѡ�񡾶�ֵ��ģʽ�������Ҷ�ģʽ��  ************/
        /***  ǿ��һ�㣺��ν�ĻҶ�ģʽ��ʵ����ֻ��2������ֵ�����Ѿ���ֵ���õĻҶ�ģʽ��  ***/

#if 0       //����ѹ��ֱ�ӷ��Ͷ�ֵ��ͼ����λ������λ��ѡ�񡾶�ֵ��ģʽ��

        //����ͼ����λ��
        vcan_sendimg(imgbuff, CAMERA_SIZE);                  //���͵���λ��

#else     //��ѹ������ֻ��2������ֵ�ĻҶ�ͼ����λ������λ��ѡ�񡾻Ҷ�ģʽ��

        img_extract(img, imgbuff,CAMERA_SIZE);                  //��ѹͼ��
        
        Find_Midline(img,midline);
        MakeUpWhiteIslands_W(img,midline);
        Find_Midline(img,midline);
        Paint_Midline(img,midline);
        
        img_compress(imgcompress,img,CAMERA_W * CAMERA_H);
        vcan_sendimg(imgcompress, CAMERA_SIZE); 
        //vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //���͵���λ��
#endif
    }
}

/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
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
#if 1             //ӥ��ֱ��ȫ�ٲɼ�������Ҫ���ж�
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