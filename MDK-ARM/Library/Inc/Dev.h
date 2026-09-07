#ifndef __Dev_H
#define __Dev_H

#include "lakiBeam.h"
#include "math.h"

#define ENABLE_FILTER  0
#define Startdis 0
#define Enddis 600 

void Dev_process(void);
float get_value(float n);

extern float n10p_dev;
extern int data_num_ok;
extern float front_dist;
extern int r_start;
extern float r_len;
extern float l_len;
extern float	r_num22;
extern float	l_num22;
extern  float Str_Line_kb[2][2];
extern  float L_black[100];
extern  float R_black[100];
extern float L_black_num[100];
extern float R_black_num[100];
extern float l_len;
extern float r_len;
extern float L_black_shift[100];
extern float R_black_shift[100];
extern float Str_Line_kb[2][2];
extern float r_sum;
extern float l_sum;
extern int M_num;
extern float r_sum0;
extern float l_sum0;
extern float dev0;
extern int lable[181];
extern PointData_XY L_point[800];
extern PointData_XY R_point[800];
extern PointData_XY L_point4[800];
extern PointData_XY R_point4[800];
extern PointData_Send L_point2[800];
extern PointData_Send R_point2[800];
extern PointData_Send M_point2[200];
extern PointData_XY M_point[200];
extern	int r_num;
extern	int l_num;
extern int r_start;
extern int l_start;
extern float track_width;
extern float last_dev0;
extern float dev_l[40];
extern float dev_r[40];
extern int len_l;
extern int len_r;
extern float taker;
extern int n;
extern int control_line;//0×ó1ÓÒ2ÖÐ
extern float kbleft[2];
extern float kbright[2];
extern float kbmid[2];
extern float dev_k;
extern float dev_b;
extern float k;
extern float b;
extern float kk;
extern float bb;
extern float w1;

void get_dev_L(PointData L_point);
void get_dev_R(PointData R_point);
void black_init(void);
void get_black(void);
void Str_Regression_Left(int startline, int endline, int checkFlag);
void Str_Regression_Right(int startline, int endline, int checkFlag);
void black_col(void);
void get_start_point2(void);
void D_control(void);
void Get_black(void);
void Cal_Dev2(void);
float calculate_polar_distance(float x1, float y1, float x2, float y2);
void Get_point(void);
void go(void);
#endif

