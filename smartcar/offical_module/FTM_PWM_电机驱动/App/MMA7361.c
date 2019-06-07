#include "include.h"
#include "MMA7361.h"

//*************�ܽ�˵��***********************
/*
  AX -> PB0 -> ADC0_SE8
  AY -> PB1 -> ADC0_SE9
  AZ -> PB2 -> ADC0_SE12
  GX -> PB3 -> ADC0_SE13
  SL -> E1 ��
  GS -> E2 ��
*/
unsigned char BUF[20];       //�������ݻ�����
				 //IIC

int32 AX,AY,AZ;
float ax,ay,az;


//*************��ʼ��MPU6050***********************
int Init_MMA7361(void)
{
  //��ʼ�� MMA7361 ���õ� ADCͨ��
  adc_init(ADC0_SE9); 
  adc_init(ADC0_SE12); 
  adc_init(ADC0_SE8);

  return 1;
}


void READ_MMA7361(void)
{
   AX =	adc_once(ADC0_SE8, ADC_12bit);
   AX -= (1184+3560)/2;
   ax = AX*2/(float)(3560-1184);		                //��ȡ����AX���ݣ�3040��1040��ʵ�ʲ�õģ������Ҳһ��

   AY =	adc_once(ADC0_SE9, ADC_12bit);
   AY -= (900+2930)/2;
   ay = AY*2/(float)(2930-900);		                //��ȡ����AY����

   AZ =	adc_once(ADC0_SE12, ADC_12bit);
   AZ -= (3415+1080)/2;
   az = AZ*2/(float)(3415-1080);	                 	//��ȡ����AZ����
  
}


