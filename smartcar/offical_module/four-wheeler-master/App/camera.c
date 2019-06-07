#include "camera.h"

/**
 * 根据图像矩阵寻找中线
 */
void Find_Midline(uint8 * img, uint8 *midline) {
	uint8 *tmpimg = img;
	int n;//表示该行白色位置的个数
	int total_address; //白色位置下标和

	for (int j = 0; j < CAMERA_H;j++) {
		n = 0;
		total_address = 0;
		for (int i = 0;i < CAMERA_W;i++) {
			if (*(tmpimg + i) == 255) {
				n++;
				total_address += i;
			}
		}
		midline[j] = total_address / n;

		tmpimg += CAMERA_W;
	}
}


/**
 * 对赛道以外的图像区域进行二次修正
 * 
 */
void MakeUpWhiteIslands_W(uint8 *img, uint8 *midline) {
	int addR = 0;
	int addL = 0;
	for (int i = 0; i < CAMERA_H; i++) {
		addL = midline[i] - 1;
		addR = midline[i] + 1;
		while (addL) {
			if (img[i*CAMERA_W + addL] == 0) {
				break;
			}
			addL--;
		}

		while (addR < CAMERA_W) {
			if (img[i*CAMERA_W + addR] == 0) {
				break;
			}
			addR++;
		}
		for (int j = 0; j < addL;j++) {
			img[i*CAMERA_W + j] = 0;
		}
		for (int j = CAMERA_W - 1; j > addR; j--) {
			img[i*CAMERA_W + j] = 0;
		}
	}
}

/**
 * 在图像矩阵中绘制中线
 * 
 */
void Paint_Midline(uint8 *img, uint8 *midline){
    for(int i=0; i<CAMERA_H ; i++){
        img[i*CAMERA_W+ midline[i]]=0;
    }
}