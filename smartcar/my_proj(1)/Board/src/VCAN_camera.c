#include "common.h"


//压缩二值化图像解压（空间 换 时间 解压）
//srclen 是二值化图像的占用空间大小
//【鹰眼解压】鹰眼图像解压，转为 二维数组 - 智能车资料区 - 山外论坛 http://vcan123.com/forum.php?mod=viewthread&tid=17&ctid=6
//解压的时候，里面有个数组，配置黑、白对应的值是多少。
void img_extract(void *dst, void *src, uint32_t srclen)
{
    uint8_t colour[2] = {255, 0}; //0 和 1 分别对应的颜色
    uint8_t * mdst = dst;
    uint8_t * msrc = src;
    //注：山外的摄像头 0 表示 白色，1表示 黑色
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
  uint8_t colour[2] = {1,0}; //0 和 1 分别对应的颜色
    uint8_t * mdst = dst;
    uint8_t * msrc = src;
    //注：山外的摄像头 0 表示 白色，1表示 黑色
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