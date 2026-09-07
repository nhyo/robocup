/**
 * @file Deploy.c
 * @brief porvide an easy way to build and modify our project
 * @author TangSong404 MindFreak(hzr)
 */
 //KKK
#include "Deploy.h"
#include "Control.h"
int time_unix = 0;
int run_times = 0;
int can_run_flag = 0;
#define Crash_Speed -35
#define Crash_K 1.2
#define Crash_Frame 4
#define Crash_TH 150
#define Crash_TIME 400

float c_lmin = 2000;
float c_rmin = 2000;
float c_mmin = 2000;
int c_time = 0;	
uint8_t c_status = 0;
uint8_t c_flag = 0;
int enc_sum = 0;
int16_t servo_pwm = 0;
uint16_t servo_max_time = 0;
int time_mac = 0;

int LEAVE_TIME = 15000;
int LEAVE_TIME2 = 15000;

uint8_t judgeCrash(void){
	if(!c_status&&c_flag){
		c_status = 1;
		c_time = time_unix;
	}
	else if(c_status==1&&time_unix-c_time>Crash_TIME){
		c_status = 0;
		c_time = 0;
	}
	return c_status;
}

void interrupt_all(void){
	time_unix++;
	if(run_times++==40){
		if(can_run_flag>20){
			encoder_get();
			Total_Control();
			control_run(Control_OutPut);
		}
		run_times = 0;
	}
	if(can_run_flag>20)time_mac++;
}

int circle_time = 0;
float back_th  =0.0f;
float top_sum = 0;
uint8_t top_num = 0;
float top = 0;
void process_after_radar(){
	
	//dataprocess init
	for(uint16_t i = 0;i < data_num;i++){
		Dataprocess[i].angle = Dataprocess_origin[data_num-i-1].angle;
		Dataprocess[i].distance = Dataprocess_origin[data_num-i-1].distance;
		Dataprocess[i].X=(Dataprocess_origin[data_num-i-1].distance * cosf(Dataprocess_origin[data_num-i-1].angle*0.01745329f));
		Dataprocess[i].Y=(Dataprocess_origin[data_num-i-1].distance * sinf(Dataprocess_origin[data_num-i-1].angle*0.01745329f));
		
		float r_dis = calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,-100.0f,100.0f);
		float l_dis = calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,100.0f,100.0f);
		float m_dis = calculate_polar_distance(Dataprocess[i].X,Dataprocess[i].Y,0.0f,100.0f);
		if(l_dis<c_lmin)c_lmin = l_dis;
		if(r_dis<c_rmin)c_rmin = r_dis;  
		if(m_dis<c_rmin)c_mmin = m_dis;  
		
		if(fabs(Dataprocess[i].angle-90.0f)<=1.3f){
			top_sum += Dataprocess[i].Y;
			top_num++;
		}
		Dataprocess_send[i].X=(uint8_t)(int)(Dataprocess[i].X/10+128);
		Dataprocess_send[i].Y=(uint8_t)(int)(Dataprocess[i].Y/10+128);
	}
	
	//speedTop
	if(top_num!=0)top = (float)(top_sum/(float)top_num);
	else top = 2000;
	top_num = 0;
	top_sum = 0.0f;
	
	//cal dev and send img
	go();
	//esp01s_send_discard();
	
	
	//go back when carsh
	if(abs((int)servo_pwm)>SERVO_LIMIT-1)servo_max_time++;
	else servo_max_time = 0;
	
	if((((kbright[0]>Crash_K&&c_rmin<Crash_TH)||(kbleft[0]<-Crash_K&&c_lmin<Crash_TH))&&servo_max_time>Crash_Frame)||c_mmin<Crash_TH-35)c_flag = 1;
	else c_flag = 0;
	
	//if(0){
	//	pwm_duty(SERVO_CH,SERVO_MID);
	//	aimspeed = Crash_Speed;
//	}
	//else{
		control_turn(-dev0,0,2,10);
		aimspeed = getaimspeed();
	//}
	
	c_lmin = 2000;
	c_rmin = 2000;
	
	circle_time = time_unix;
	can_run_flag++;
}

extern TIM_HandleTypeDef htim1;
void init_all(void){
//	vofa_init();
	control_init();
	lakibeam_init(process_after_radar);
	HAL_TIM_Base_Start_IT(&htim1);
}

void loop_all(void){
	lakibeam_sampling();
}








