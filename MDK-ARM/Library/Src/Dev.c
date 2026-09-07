/**
 * @file Dev.c
 * @brief devitation caculation core codes
 * @author MindFreak(hzr)
 */
#include "Dev.h"
#include "math.h"
#include <stdlib.h>
#include "Control.h"
#include "Img.h"
int Max_dev = 50; //具体数值应可调
float n10p_dev = 0.0f;
float DeviationVar = 0.0f;
float Pre_Last_DeviationVar = 0.0f;
float Last_DeviationVar = 0.0f;
//float dist = 0.0f;
//float last_dist = 0.0f;
float Dev_right = 0.0f;
float Dev_left = 0.0f;
int data_num_ok = 0;
int last_data_num_ok = 0;
float front_dist = 0.0f;
int len_l = 0;
int len_r = 0;
float taker = 0.0f;

/*******************************************************************/
////分离开的左右点
PointData_XY L_point[800];
//PointData L_point3[800];
PointData_XY L_point4[800];
PointData_XY R_point[800];

//PointData R_point3[800];
PointData_XY R_point4[800];
PointData_XY M_point[200];
PointData_Send L_point2[800];
PointData_Send R_point2[800];
PointData_Send M_point2[200];
int start_line=20;
int end_line=50;

int r_num;
int l_num;
int M_num;
int r_start=0;
float track_width=1400;

float L_black[100];
float R_black[100];

float L_black_num[100];
float R_black_num[100];

float L_black_shift[100];
float R_black_shift[100];

float r_len;
float l_len;

float r_num22=0;
float l_num22=0;

float dev0=0;
float last_dev0=0;

float r_sum;
float l_sum;
float r_sum0;
float l_sum0;

int r_flag=0;
int l_flag=0;

uint16_t l_firstp_i = 0;
uint16_t r_firstp_i = 0;


//视野
//TODO:dis
int getblack(float x,float y)
{
	if(fabs(x)<800.0f&&y<1200.0f)return 1;
	else return 0;
}

void get_start_point2()
	{
		
	  r_flag=0;
    l_flag=0;
		
    l_len=0;
		r_len=0;
		
	 r_sum=0;
	 l_sum=0;
	 r_sum0=0;
	 l_sum0=0;
   r_num=0;
	 l_num=0;
	for(int i=0;i<800;i++)
	{

		L_point[i].X=0;
		L_point[i].Y=0;
		R_point[i].X=0;
		R_point[i].Y=0;
		M_point[i].X=0;
		M_point[i].Y=0;
		if(i<100)
		{
		L_black[i]=0;
		R_black[i]=0;
	  L_black_num[i]=0;
    R_black_num[i]=0;
	  L_black_shift[i]=0;
    R_black_shift[i]=0;
		}
	}
	l_firstp_i = 1;
	r_firstp_i = 1;
		//60
		while(!(Dataprocess[l_firstp_i].angle<40&&getblack(Dataprocess[l_firstp_i].X,Dataprocess[l_firstp_i].Y)
			&&(calculate_polar_distance(Dataprocess[l_firstp_i].X,Dataprocess[l_firstp_i].Y,Dataprocess[l_firstp_i+1].X,Dataprocess[l_firstp_i+1].Y)<50
			||calculate_polar_distance(Dataprocess[l_firstp_i].X,Dataprocess[l_firstp_i].Y,Dataprocess[l_firstp_i-1].X,Dataprocess[l_firstp_i-1].Y)<50)))
			if(l_firstp_i++>6)break;
		if(l_firstp_i<=6){
	    L_point4[0].X=Dataprocess[l_firstp_i].X;
			L_point4[0].Y=Dataprocess[l_firstp_i].Y;
			//L_point2[0].X=(uint8_t)(int)(L_point[0].X/10+128);
			//L_point2[0].Y=(uint8_t)(int)(L_point[0].Y/10+128);
			l_flag=1;
			l_num=1;
		}
		//140
		while(!(Dataprocess[data_num-1-r_firstp_i].angle>140&&getblack(Dataprocess[data_num-1-r_firstp_i].X,Dataprocess[data_num-1-r_firstp_i].Y)
			&&(calculate_polar_distance(Dataprocess[data_num-1-r_firstp_i].X,Dataprocess[data_num-1-r_firstp_i].Y,Dataprocess[data_num-2-r_firstp_i].X,Dataprocess[data_num-2-r_firstp_i].Y)<50
		||calculate_polar_distance(Dataprocess[data_num-1-r_firstp_i].X,Dataprocess[data_num-1-r_firstp_i].Y,Dataprocess[data_num-r_firstp_i].X,Dataprocess[data_num-r_firstp_i].Y)<50)))
				if(r_firstp_i++>6)break;
		if(r_firstp_i<=6){
		  R_point4[0].X=Dataprocess[data_num-1-r_firstp_i].X;
			R_point4[0].Y=Dataprocess[data_num-1-r_firstp_i].Y;
			//R_point2[0].X=(uint8_t)(int)(R_point[0].X/10+128);
			//R_point2[0].Y=(uint8_t)(int)(R_point[0].Y/10+128);
			r_flag=1;
			r_num=1;
		}
			
			
	}
	
	float calculate_polar_distance(float x1, float y1, float x2, float y2) {
    // 计算两点之间的距离
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
	
float last_track_width = 0;
float Get_track_width()
{
	
	float r_sum=0;
	float l_sum=0;
	
	if(L_point4[0].X==0||R_point4[0].X==0)return last_track_width;
	
	for(int i=0;i<1;i++)
	{
		l_sum+=L_point4[i].X;
		r_sum+=R_point4[i].X;
	}
		return (l_sum/1)-(r_sum/1);
}          

float r_len2=0;
float l_len2=0;
float r_len_y=0;
float l_len_y=0;
float r_len_x=0;
float l_len_x=0;

int M_num5=0;

int clip(int x, int low, int up) {
    return x > up ? up : x < low ? low : x;
}
//补线
void get_midR(int start , float track_width0 )
{
	    for (int i = 2; i < r_num-3; i++) {
        float dx = R_point4[clip(i + 2, 0, r_num-3)].X - R_point4[clip(i - 2, 0, r_num-3)].X;
        float dy = R_point4[clip(i + 2, 0, r_num-3)].Y - R_point4[clip(i - 2, 0, r_num-3)].Y;
        float dn = sqrtf(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        R_point[i-2].X = R_point4[i].X +dy * track_width0;
        R_point[i-2].Y = R_point4[i].Y - dx * track_width0;
			R_point2[i-2].X=(uint8_t)(int)(R_point[i-2].X/10+128);
   		 R_point2[i-2].Y=(uint8_t)(int)(R_point[i-2].Y/10+128);
    }
			r_num=r_num-7;
}


void get_midL(int start , float track_width0 )
{
	    for (int i = 2; i < l_num-3; i++) {
        float dx = L_point4[clip(i + 2, 0, l_num-3)].X - L_point4[clip(i - 2, 0, l_num-3)].X;
        float dy = L_point4[clip(i + 2, 0, l_num-3)].Y - L_point4[clip(i - 2, 0, l_num-3)].Y;
        float dn = sqrtf(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        L_point[i-2].X = L_point4[i].X - dy * track_width0;
        L_point[i-2].Y = L_point4[i].Y + dx * track_width0;
			 L_point2[i-2].X=(uint8_t)(int)(L_point[i-2].X/10+128);
   		 L_point2[i-2].Y=(uint8_t)(int)(L_point[i-2].Y/10+128);
    }
			l_num=l_num-7;
}
//滤波
void blur_pointsL(int kernel)
{
    int half = kernel / 2;
    for (int i = 0; i < l_num; i++) {
         L_point[i].X =  L_point[i].Y = 0;
        for (int j = -half; j <= half; j++) {
             L_point[i].X += L_point4[clip(i + j, 0, l_num - 1)].X * (half + 1 - abs(j));
             L_point[i].Y +=L_point4[clip(i + j, 0, l_num - 1)].Y * (half + 1 - abs(j));
        }
         L_point[i].X /= (2 * half + 2) * (half + 1) / 2;
         L_point[i].Y /= (2 * half + 2) * (half + 1) / 2;
			  //	L_point2[i].X=(uint8_t)(int)(L_point[i].X/10+128);
			   // L_point2[i].Y=(uint8_t)(int)(L_point[i].Y/10+128);
    }
}

void blur_pointsR(int kernel)
{
    int half = kernel / 2;
    for (int i = 0; i < r_num; i++) {
         R_point[i].X =  R_point[i].Y = 0;
        for (int j = -half; j <= half; j++) {
             R_point[i].X += R_point4[clip(i + j, 0, r_num - 1)].X * (half + 1 - abs(j));
             R_point[i].Y +=R_point4[clip(i + j, 0, r_num - 1)].Y * (half + 1 - abs(j));
        }
         R_point[i].X /= (2 * half + 2) * (half + 1) / 2;
         R_point[i].Y /= (2 * half + 2) * (half + 1) / 2;
				 //	R_point2[i].X=(uint8_t)(int)(R_point[i].X/10+128);
			   // R_point2[i].Y=(uint8_t)(int)(R_point[i].Y/10+128);
				
    }
}
//等距
void get_L_line(float dis )
{
	//int n=190;
	    float remain = 0.f;
    int len = 0;
    for(int i=0; i<l_num-1 ; i++){
        float x0 =  L_point[i].X;
        float y0 =  L_point[i].Y;
        float dx =  L_point[i+1].X - x0;
        float dy =  L_point[i+1].Y - y0;
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;

			while(remain < dn ){
            x0 += dx * remain;
            L_point4[len].X = x0;
            y0 += dy * remain;
            L_point4[len].Y = y0;
        	L_point2[len].X=(uint8_t)(int)(L_point4[len].X/10+128);
			    L_point2[len].Y=(uint8_t)(int)(L_point4[len].Y/10+128);
            len++;
            dn -= remain;
            remain = dis;
        }
        remain -= dn;
    }
    l_num = len;
}


void get_R_line(float dis )
{
	    float remain = 0.f;
    int len = 0;
    for(int i=0; i<r_num-1 ; i++){
        float x0 =  R_point[i].X;
        float y0 =  R_point[i].Y;
        float dx =  R_point[i+1].X - x0;
        float dy =  R_point[i+1].Y - y0;
        float dn = sqrtf(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;

        while(remain < dn){
            x0 += dx * remain;
            R_point4[len].X = x0;
            y0 += dy * remain;
            R_point4[len].Y = y0;
        	R_point2[len].X=(uint8_t)(int)(R_point4[len].X/10+128);
			    R_point2[len].Y=(uint8_t)(int)(R_point4[len].Y/10+128);
            len++;
            dn -= remain;
            remain = dis;
        }
        remain -= dn;
    }
    r_num = len;
}

void get_M_lineL(int start ,int end ,float dis )
{
	    float remain = 0.f;
    int len = 0;
    for(int i=start; i<end-6; i++){
        float x0 =  L_point[i].X;
        float y0 =  L_point[i].Y;
        float dx =  L_point[i+1].X - x0;
        float dy =  L_point[i+1].Y - y0;
        float dn = sqrtf(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;
        if(dx>0&&dy<0)continue;
        while(remain < dn){
            x0 += dx * remain;
            L_point4[len].X = x0;
            y0 += dy * remain;
            L_point4[len].Y = y0;
        	L_point2[len].X=(uint8_t)(int)(L_point4[len].X/10+128);
			    L_point2[len].Y=(uint8_t)(int)(L_point4[len].Y/10+128);
            len++;
            dn -= remain;
            remain = dis;
        }
        remain -= dn;
    }
    l_num = len;
	//	M_num = len;
}

void get_M_lineR(int start ,int end ,float dis )
{
	    float remain = 0.f;
    int len = 0;
    for(int i=start; i<end-6; i++){
        float x0 =  R_point[i].X;
        float y0 =  R_point[i].Y;
        float dx =  R_point[i+1].X - x0;
        float dy =  R_point[i+1].Y - y0;
        float dn = sqrtf(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;

        while(remain < dn ){
            x0 += dx * remain;
            R_point4[len].X = x0;
            y0 += dy * remain;
            R_point4[len].Y = y0;
        	R_point2[len].X=(uint8_t)(int)(R_point4[len].X/10+128);
			    R_point2[len].Y=(uint8_t)(int)(R_point4[len].Y/10+128);
            len++;
            dn -= remain;
            remain = dis;
        }
        remain -= dn;
    }
    r_num = len;
}

void Get_point()
{
 int t1=0;
	int t2=0;
  r_len2=0;
	l_len2=0;
	l_len_y=0;
	r_len_y=0;
	l_len_x=0;
	r_len_x=0;
	static int t3=0;
	static int t4=0;
	
	
	float first_len = calculate_polar_distance(Dataprocess[l_firstp_i+1].X,Dataprocess[l_firstp_i+1].Y,Dataprocess[l_firstp_i].X,Dataprocess[l_firstp_i].Y);
	for(int i=l_firstp_i+1;i<800&&l_flag;i++)
	{
		//if(first_len>200)break;
		
			if(calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,L_point4[l_num-1].X,L_point4[l_num-1].Y)>200){
			t3++;
			continue;
		}else{

		if ((Dataprocess[i].distance!=0&&calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,Dataprocess[i-1].X,Dataprocess[i-1].Y)<200&&
			getblack(Dataprocess[i].X,Dataprocess[i].Y)/*&&((l_len_y>20&&Dataprocess[i].Y<300)||(l_len2>20&&Dataprocess[i].Y>=300))*/)){
			t3 = 0;

			L_point4[l_num].X=Dataprocess[i].X;
		 	L_point4[l_num].Y=Dataprocess[i].Y;
			L_point2[l_num].X=(uint8_t)(int)(L_point4[l_num].X/10+128);
			L_point2[l_num].Y=(uint8_t)(int)(L_point4[l_num].Y/10+128);
	//		l_len+=calculate_polar_distance(L_point[l_num].X,L_point[l_num].Y,L_point[l_num-1].X,L_point[l_num-1].Y);
			l_num++;
		}else t3 = 0;
	}
   if(t3>6){
		 t3=0;
		 break;
	 }
	}
	
	first_len = calculate_polar_distance(Dataprocess[data_num-2-r_firstp_i].X,Dataprocess[data_num-2-r_firstp_i].Y,Dataprocess[data_num-1-r_firstp_i].X,Dataprocess[data_num-1-r_firstp_i].Y);
	for(int i=data_num-r_firstp_i-2;r_flag==1&&i>0;i--)
	{
	//	if(first_len>200)break;
		if(calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,R_point4[r_num-1].X,R_point4[r_num-1].Y)>300){
			t4++;
			continue;
		}else{

		if (Dataprocess[i].distance!=0&&calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,Dataprocess[i+1].X,Dataprocess[i+1].Y)<300&&
			getblack(Dataprocess[i].X,Dataprocess[i].Y)/*&&((r_len_y>20&&Dataprocess[i].Y<300)||(r_len2>20&&Dataprocess[i].Y>=300))*/)
		{
			t4=0;

			R_point4[r_num].X=Dataprocess[i].X;
			R_point4[r_num].Y=Dataprocess[i].Y;
			R_point2[r_num].X=(uint8_t)(int)(R_point4[r_num].X/10+128);
			R_point2[r_num].Y=(uint8_t)(int)(R_point4[r_num].Y/10+128);
//			r_len+=calculate_polar_distance(R_point[r_num].X,R_point[r_num].Y,R_point[r_num-1].X,R_point[r_num-1].Y);
			r_num++;
		}else t4 = 0;
	}
		if(t4>6){
		 t4=0;
		 break;
	 }
	}
		
	
	//去噪

	blur_pointsL(7);
	blur_pointsR(7);

	//等距
	get_L_line(20.0 );
	get_R_line(20.0 );
	
//	roadblockGo(roadblockJudge());
	
  r_num22=r_len;
	l_num22=l_len;

	//赛道
	
	last_track_width = track_width;
	track_width=Get_track_width();
//	//mid
get_midL(0,track_width/2 );
get_midR(0,track_width/2 );

//get_M_lineL(0,l_num,20.0);
//get_M_lineR(0,r_num,20.0);
	
}


float r_num0=0;
float l_num0=0;
void Get_black()
	{
		int len=r_num>l_num ? r_num:l_num;
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(L_point[i].Y>i-5&&L_point[i].Y<i+5)
				{
					L_black_num[i]++;
					L_black_shift[i]+=L_point[i].X;
				}
				
				if(R_point[i].Y>i-5&&R_point[i].Y<i+5)
				{
					L_black_num[i]++;
					L_black_shift[i]+=L_point[i].X;
				}
				
				if(L_point[i].Y>=i+5&&R_point[i].Y>=i+5)
				{
					break;
				}
			}
			if(L_black_num[i]==0) l_num0=i;
			if(R_black_num[i]==0) r_num0=i;
			if(L_black_num[i]==0&&R_black_num[i]==0)break;
		}
		
	 for(int i=0;i<100;i++ )
		{
			if(L_black_num[i]==0)
			{
				L_black[i]=0;
			}
			else
			{
				L_black[i]=L_black_shift[i]/ L_black_num[i];
			}
			if(R_black_num[i]==0)
			{
				R_black[i]=0;
			}
			else
			{
				R_black[i]=R_black_shift[i]/ R_black_num[i];
			}
		}
 	}
	
	///////////////////////////////////////////////////////////////////////
	//TODO:kk
int control_line=2;//0左1右2中
float kbleft[2] = {0};
float kbright[2] = {0};
float kbmid[2] = {0};
float dev_k=0;
float dev_b=0;
//float kl=1400;
//float kr=1400;
//float b=200;
float kl=1450;
float kr=1550;
float b=200;
float kk=0;
float bb=0;


//最小二乘法拟合
void getline()
	{
		float sumx = 0;
    float sumy = 0;
    float sumxy = 0;
    float sumx2 = 0;
    float x;
    float y;

//    for (int i = 0; i < M_num; i++)
//    {
//      y = M_point[i].X/10;
//      x =M_point[i].Y/10;
//      sumx += x;
//      sumy += y;
//      sumxy += x * y;
//      sumx2 += x * x;
//    }
//	  kbmid[0] = (  (M_num)* sumxy - sumx * sumy) / ( (M_num) * sumx2 - sumx * sumx);
//    kbmid[1] = sumy / (M_num) - kbmid[0] * sumx /  (M_num);
//		//n = 0;
//		sumx = 0;
//    sumy = 0;
//    sumxy = 0;
//		sumx2 = 0;
     for (int i = 0; i < r_num; i++)
     {
				y = R_point[i].X/10;
				x =R_point[i].Y/10;
				sumx += x;
				sumy += y;
				sumxy += x * y;
				sumx2 += x * x;
			}
		 if(r_num * sumx2 - sumx * sumx==0||r_num==0){
			kbright[0] = 0;
			kbright[1] = 0;
		 }else{
			kbright[0] = (r_num * sumxy - sumx * sumy) / (r_num * sumx2 - sumx * sumx);
			kbright[1] = sumy / r_num -  kbright[0] * sumx / r_num;
		 }
		sumx = 0;
    sumy = 0;
    sumxy = 0;
		sumx2 = 0;
     for (int i = 0; i < l_num; i++)
     {
				y = L_point[i].X/10;
				x =L_point[i].Y/10;
				sumx += x;
				sumy += y;
				sumxy += x * y;
				sumx2 += x * x;
			}
			if(l_num * sumx2 - sumx * sumx==0||l_num==0){
				kbleft[0] = 0;
				kbleft[1] = 0;
			}else{
				kbleft[0] = (l_num * sumxy - sumx * sumy) / (l_num * sumx2 - sumx * sumx);
				kbleft[1] = sumy / l_num - kbleft[0] * sumx / l_num;
			}
	}
	
	
uint8_t control_times = 0;
uint8_t new_control = 3;
uint8_t last_control = 3;
float last_l_len = 0;
float last_r_len = 0;
float w1 = 0.0f;
const uint16_t change_len = 720;
#define FRAME_TIMES 0
	//TODO:len
	void D_control()
	{
		//根据线长选线
//		do{
//			last_control = new_control;
//			if(l_len<change_len&&r_len<change_len){
//				new_control=3;
//				break;
//			}
//			if(r_len<change_len&&l_len>change_len){
//				new_control=0;
//				break;
//			}
//			if(l_len<change_len&&r_len>change_len){
//				new_control=1;
//				break;
//			}
//			if(l_len>change_len&&r_len>change_len){
//				new_control=2;
//				break;
//			}
//		}while(0);
//		if(last_control==new_control)control_times++;
//		else control_times = 0;
//		if(control_times>FRAME_TIMES||l_len<10||r_len<10||new_control==3)control_line = new_control;
		if((r_num<5&&l_num<5))control_line = 3;
		else control_line = 2;
		last_l_len = l_len;
		last_r_len = r_len;
		getline();
		
		//算偏差
	
		float k2;
		if(dev0>0)
		k2 = kl/100.0f;
		else k2 = kr/100.0f;
		bb=b/100.0f;
		//kk=k2*bb*10;
		kk=k2*10;
		if(control_line==2)
		{
			//dev_k=kbmid[0];
			//dev_b=kbmid[1];
			float diff = (-l_num + r_num)/80.0f;
			w1 = 1 / (1 + expf(diff));
			float w2 = 1 - w1;
			
			uint8_t error_num = 0;
			if(isnan(kbright[0])||isnan(kbright[1])){
				kbright[0] = 0;
				kbright[1] = 0;
				error_num++;
			}
			if((isnan(kbmid[0])||isnan(kbmid[1])))
			{
				kbmid[0] = 0;
				kbmid[1] = 0;
				error_num++;
			}
			if(error_num==2)dev0 = last_dev0;
			else{
				dev_k= kbright[0]*w2+kbleft[0]*w1;
				dev_b=kbright[1]*w2+kbleft[1]*w1;
//			dev_k= kbleft[0];
//			dev_b=kbleft[1];
//				dev_k= kbright[0];
//				dev_b=kbright[1];
//				dev_b=kbright[1];
//				if(r_num>l_num)
//				{
//				dev_k= kbright[0];
//				dev_b=kbright[1];
//				}
//			if(r_num<l_num)
//			{
//			dev_k= kbleft[0];
//			dev_b=kbleft[1];
//			}
				last_dev0=dev0;
				dev0=(dev_k*kk+dev_b*bb);
				//control_turn(-dev0,0,1.8,10);
				if(isnan(dev0))dev0 = last_dev0;
			}
		}/*
		else if(control_line==1)
		{
			dev_k=kbright[0];
			dev_b=kbright[1];
			dev0=dev_k*kk+dev_b*bb;
		}
		else if(control_line==0)
		{
			dev_k=kbleft[0];
			dev_b=kbleft[1];
			dev0=dev_k*kk+dev_b*bb;
		}*/
		else if(control_line==3)
			dev0=last_dev0;
		//control_turn(-dev0,0,2,10);
		//control_turn(-dev0,0.03,0.45,0);
	}
	
void go(){
		get_start_point2();
		Get_point();
		
		getline();
		
		D_control();
}

	