#ifndef K60_CAMERA_H_INCLUDED
#define K60_CAMERA_H_INCLUDED


#include "include.h"
#include "common.h"


#define WHITE 0x00
#define BLACK 0xFF
#define STEP1 5
#define STEP2 15 //STEP1+STEP2==20
typedef struct
{
    float err_1,err_2;
}CAMERA_ERR;

void final_midline(const uint8 *midline, uint8 *f_midline);

void Find_Midline(uint8 *img, uint8 *midline);


void MakeUpWhiteIslands_W(uint8 *img, const uint8 *midline);


void Paint_Midline(uint8 *img, const uint8 *midline);

void calc_camera_err (const uint8 *f_midline, CAMERA_ERR *c_err);
#endif // K60_CAMERA_H_INCLUDED