# Four-Wheeler
上传了官方鹰眼识别程序，内容有所改动：
1.  在VCAN_camera.c中添加了void img_compress(void *dst, void *src, uint32_t srclen)函数，并在VCAN_camera.h中做了extern声明，可将解压后的摄像头数据重新压缩，以提高串口传输效率。

2.  以每一行上白色点下标为依据寻找道路中点，并通过补黑道路以外的干扰进行二次修正，最终在串口传回图像中添加道路中线（黑色）。
