#include "MPU6050.h"
#include "include.h"

volatile int16 MPU6050_ACCEL_XOUT_DATA=0;
volatile int16 MPU6050_ACCEL_YOUT_DATA=0;
volatile int16 MPU6050_ACCEL_ZOUT_DATA=0;
volatile int16 MPU6050_TEMP_OUT_DATA=0;
volatile int16 MPU6050_GYRO_XOUT_DATA=0;
volatile int16 MPU6050_GYRO_YOUT_DATA=0;
volatile int16 MPU6050_GYRO_ZOUT_DATA=0;
/*
void MPU6050_Init(void)
{
  i2c_init(MPU6050_I2C_Moudle,0,0,4);
  i2c_writeaddr(MPU6050_I2C_Moudle, MPU6050_ADDRESS,MPU6050_PWR_MGMT_1, 0x00);
  i2c_writeaddr(MPU6050_I2C_Moudle, MPU6050_ADDRESS,MPU6050_PWR_MGMT_2, 0x00);
  i2c_writeaddr(MPU6050_I2C_Moudle, MPU6050_ADDRESS,MPU6050_CONFIG, 0x06);//��ͨ�˲�������5Hz
  i2c_writeaddr(MPU6050_I2C_Moudle, MPU6050_ADDRESS,MPU6050_GYRO_CONFIG, 0x08);//���Լ�   ��500 ��/s
  i2c_writeaddr(MPU6050_I2C_Moudle, MPU6050_ADDRESS,MPU6050_ACCEL_CONFIG, 0x08);//���Լ�  ��4g
}*/
//--------------------------------------------------------------
/*!
 *  @brief      i2c��ʼ��
 *  @param      I2Cn_e        I2Cģ��(I2C0��I2C1)
 *  @since      v1.0
 *  Sample usage:       MPU6050_Init(MPU6050_I2C_Moudle_1)     //��ʼ��i2c 1
 */
void MPU6050_Init(I2Cn_e i2cn)
{
  i2c_init(i2cn,400*1000);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_PWR_MGMT_1, 0x00);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_PWR_MGMT_2, 0x00);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_CONFIG, 0x06);//��ͨ�˲�������5Hz
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_GYRO_CONFIG, 0x08);//���Լ�   ��500 ��/s
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_ACCEL_CONFIG, 0x08);//���Լ�  ��4g
} 

//----------------------------------------------------------------------
/*!
 *  @brief      ��ȡ����
 *  @param      I2Cn_e        I2Cģ��(I2C0��I2C1)
 *  @param      Addr         �ӻ��Ĵ�����ַ
 *  @param      Data        ����
 *  @since      v1.0
 *  Sample usage:       MPU6050_GetDoubleData(MPU6050_I2C_Moudle_1 , MPU6050_GYRO_YOUT)��
 */
int16 MPU6050_GetDoubleData(I2Cn_e i2cn ,uint8 Addr)
{
  uint16 data=0x0000;
  data=i2c_read_reg(i2cn,MPU6050_ADDRESS, Addr);
  data=(uint16)((data<<8)&0xff00);
  data+=i2c_read_reg(i2cn,MPU6050_ADDRESS, Addr+1);
  
  return (int16)data;//�ϳ����ݣ�Ϊ�з���������
  
}