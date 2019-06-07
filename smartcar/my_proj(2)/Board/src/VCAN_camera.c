#include "common.h"


//ѹ����ֵ��ͼ���ѹ���ռ� �� ʱ�� ��ѹ��
//srclen �Ƕ�ֵ��ͼ���ռ�ÿռ��С
//��ӥ�۽�ѹ��ӥ��ͼ���ѹ��תΪ ��ά���� - ���ܳ������� - ɽ����̳ http://vcan123.com/forum.php?mod=viewthread&tid=17&ctid=6
//��ѹ��ʱ�������и����飬���úڡ��׶�Ӧ��ֵ�Ƕ��١�
void img_extract(void *dst, void *src, uint32_t srclen)
{
    uint8_t colour[2] = {255, 0}; //0 �� 1 �ֱ��Ӧ����ɫ
    uint8_t * mdst = dst;
    uint8_t * msrc = src;
    //ע��ɽ�������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8_t tmpsrc;
    while(srclen --)
    {
        tmpsrc = *msrc++;
        *mdst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}
void img_compress(void *dst, void *src, uint32_t srclen)
{
  uint8_t colour[2] = {1,0}; //0 �� 1 �ֱ��Ӧ����ɫ
    uint8_t * mdst = dst;
    uint8_t * msrc = src;
    //ע��ɽ�������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8_t tmpdst;
    while(srclen){
      tmpdst = 0;
      tmpdst+=(colour[(*msrc++)%2])<<7;
      tmpdst+=(colour[(*msrc++)%2])<<6;
      tmpdst+=(colour[(*msrc++)%2])<<5;
      tmpdst+=(colour[(*msrc++)%2])<<4;
      tmpdst+=(colour[(*msrc++)%2])<<3;
      tmpdst+=(colour[(*msrc++)%2])<<2;
      tmpdst+=(colour[(*msrc++)%2])<<1;
      tmpdst+=(colour[(*msrc++)%2])<<0;
      *mdst++ = tmpdst;
      //*mdst++ = (*msrc++)*pow(2,7)+(*msrc++)*pow(2,6)+(*msrc++)*pow(2,5)+(*msrc++)*pow(2,4)+(*msrc++)*pow(2,3)+(*msrc++)*pow(2,2)+(*msrc++)*pow(2,1)+(*msrc++)*pow(2,0);
      srclen-=8;
    }
}