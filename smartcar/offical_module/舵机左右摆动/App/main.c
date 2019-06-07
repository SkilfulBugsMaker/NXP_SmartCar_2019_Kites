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
  * @version    v5.0
  * @date       2013-08-28
  */

#include "common.h"
#include "include.h"






/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� S3010��� ����ʵ�� ,ɽ�� �ṩ�� �������ģ�飬�ܽŶ����� MOS �ܸ��룬�ź��Ƿ���ġ�
                ���糣��� �ߵ�ƽ ʹ��
                ������ϣ��뿴�������ӣ�
                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=25
 */
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