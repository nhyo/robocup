//#include "Img.h"

//uint8_t roadblock_flag = 0;
//float break_x[4];
//float break_y[4];
//uint8_t roadblockJudge(void){
//	float break_dis = 60.0f;
//	float break_x_ = 50.0f;
//	uint8_t break_num = 0;
//	uint8_t block_num = 0;
//	float remote_x = 0.0f;
//	float remote_y = 0.0f;
//	float remote_x2 = 0.0f;
//	float remote_y2 = 0.0f;
//	for(uint16_t i = 1;i<data_num-2;i++){
//		if(Dataprocess[i].Y>1400&&Dataprocess[i-1].Y<1400){
//			remote_x = Dataprocess[i-1].X;
//			remote_y = Dataprocess[i-1].Y;
//		}
//		if(Dataprocess[i+1].Y<1400&&Dataprocess[i].Y>1400){
//			remote_x2 = Dataprocess[i+1].X;
//			remote_y2 = Dataprocess[i+1].Y;
//		}
//		if(Dataprocess[i].Y>1400)continue;
//		if(
//		(Dataprocess[i-1].Y>1400&&calculate_polar_distance(remote_x,remote_y,Dataprocess[i].X,Dataprocess[i].Y)>break_dis
//		&&fabs(remote_x-Dataprocess[i].X)>break_x_)||
//		(calculate_polar_distance(Dataprocess[i-1].X,Dataprocess[i-1].Y,Dataprocess[i].X,Dataprocess[i].Y)>break_dis
//		&&fabs(Dataprocess[i-1].X-Dataprocess[i].X)>break_x_)||
//		(calculate_polar_distance(Dataprocess[i+1].X,Dataprocess[i+1].Y,Dataprocess[i].X,Dataprocess[i].Y)>break_dis
//		&&fabs(Dataprocess[i+1].X-Dataprocess[i].X)>break_x_)
//		){
//			break_x[break_num] = Dataprocess[i].X;
//			break_y[break_num] = Dataprocess[i].Y;
//			break_num++;
//		}
//		if(break_num>0)block_num++;
//		if(break_num>=2&&block_num>35){
//			roadblock_flag = 1;
//			float dis1 = calculate_polar_distance(remote_x,remote_y,break_x[0],break_y[0]);
//			float dis2 = calculate_polar_distance(remote_x2,remote_y2,break_x[1],break_y[1]);
//			if(dis1>dis2)return 2;
//			else return 1;
//		}
//	}
//	roadblock_flag = 0;
//	return 0;
//}

//void roadblockGo(uint8_t flag){
//	if(flag==1){
//		l_num = r_num;
//		for(uint16_t i = 0;i<l_num;i++){
//			L_point4[i].X  = R_point4[i].X+500;
//			L_point4[i].Y  = R_point4[i].Y;
//		}
//	}
//	
//	else if(flag==2){
//		r_num = l_num;
//		for(uint16_t i = 0;i<r_num;i++){
//			R_point4[i].X  = L_point4[i].X-500;
//			R_point4[i].Y  = L_point4[i].Y;
//		}
//	}
//}
//uint16_t l_block_cnt = 0;
//uint16_t r_block_cnt = 0;
//uint8_t roadblock_flag = 0;
//uint8_t roadblockJudge(void){
//	for(uint16_t i=1;i<l_num;i++)
//		if(Dataprocess[i-1].Y>Dataprocess[i].Y)
//			l_block_cnt++;
//	if(l_block_cnt>3&&l_num<80)return 1;
//	
//	for(uint16_t i=1;i<r_num;i++)
//		if(Dataprocess[i-1].Y>Dataprocess[i].Y)
//			r_block_cnt++;
//	if(r_block_cnt>3&&r_num<80)return 2;
//	return 0;
//}

//void roadblockGo(uint8_t flag){
//	roadblock_flag = flag;
//	if(flag==1){
//		l_num = r_num;
//		for(uint16_t i = 0;i<l_num;i++){
//			L_point4[i].X  = R_point4[i].X+500;
//			L_point4[i].Y  = R_point4[i].Y;
//		}
//	}else if(flag==2){
//		r_num = l_num;
//		for(uint16_t i = 0;i<r_num;i++){
//			R_point4[i].X  = L_point4[i].X-500;
//			R_point4[i].Y  = L_point4[i].Y;
//		}
//	}
//}

#include "Img.h"

uint8_t roadblock_flag = 0;
uint16_t l_block_cnt = 0;
uint16_t r_block_cnt = 0;
uint16_t l_top_i = 0;
float l_top_y = 0.0f;
uint16_t r_top_i = 0;
float r_top_y = 0.0f;
uint16_t l_right_i = 0;
float l_right_x = -2000.0f;
uint16_t r_left_i = 0;
float r_left_x = 2000.0f;

uint8_t roadblockJudge(void){
	r_block_cnt = 0;
	l_block_cnt = 0;
	for(uint16_t i = 0;i<r_num-2;i++){
			if(calculate_polar_distance(R_point4[i].X,R_point4[i].Y,R_point4[r_num-1].X,R_point4[r_num-1].Y)<350)
				r_block_cnt++;
	}
	if(r_block_cnt>20)return 2;
	for(uint16_t i = 0;i<l_num-2;i++){
			if(calculate_polar_distance(L_point4[i].X,L_point4[i].Y,L_point4[l_num-1].X,L_point4[l_num-1].Y)<350)
				l_block_cnt++;
	}
	if(l_block_cnt>20)return 1;
	return 0;
}

uint8_t block_time = 0;
uint8_t block_time2 = 0;
void roadblockGo(uint8_t flag){
	if(block_time!=0){
		block_time--;
		l_num = r_num;
		for(uint16_t i = 0;i<l_num;i++){
			L_point4[i].X  = R_point4[i].X+900;
			L_point4[i].Y  = R_point4[i].Y;
		}
	}else if(block_time2!=0){
		block_time2--;
		r_num = l_num;
		for(uint16_t i = 0;i<r_num;i++){
			R_point4[i].X  = L_point4[i].X-900;
			R_point4[i].Y  = L_point4[i].Y;
		}
	}
	if(flag==1&&block_time2==0)block_time=11;
	if(flag==2&&block_time==0)block_time2=11;
}