#ifndef K60_SERVO_H_INCLUDED
#define K60_SERVO_H_INCLUDED

#define SERVO_FTM FTM1		//FTM
#define SERVO_CH FTM_CH0	//ͨ��
#define	SERVO_HZ 100		//Ƶ��
#define INIT_DUTY 1410      //��ʼ��ռ�ձȣ�����ǶȲ��Ǻ�׼

#define LEFT_BOUND_DUTY 1630 //��ת�߼�ռ�ձ�
#define RIGHT_BOUND_DUTY 1200 //��ת�߼�ռ�ձ�

/********************************************************/

//��ģ������
//��10000u�ľ����£�
//���ﵽ1200��ռ�ձȵ�����´ﵽ��ת���ޣ�
//���ﵽ1630��ռ�ձȵ�����´ﵽ��ת���ޣ�
//��void set_servo_angle (int angle)�У�
//����Ϊ0-1000��������ֵ��
//����0��Ӧ����ת��1000��Ӧ����ת��

/********************************************************/


//�����ʼ������
void servo_init(void);


//�������Ƕȣ���Ӧ0-900,�뽫PTA8��Ӧ��FTM����ռ�ձȾ��ȸ�Ϊ10000u
//���ȶ�����MK60_FTM.h
void set_servo_angle (int angle);

#endif // K60_SERVO_H_INCLUDED