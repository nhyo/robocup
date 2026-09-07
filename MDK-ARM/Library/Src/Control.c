/**
 * @file Control.c
 * @brief conrol servo and motor (pid)
 * @author MindFreak(hzr)
 */
#include "Control.h"
#include "math.h"
#include "dev.h"
void control_init(void){
	pwm_init();
	pwm_duty(SERVO_CH,SERVO_MID);
	pwm_duty(MOTOR_CH1,0);
	pwm_duty(MOTOR_CH2,0);
	encoder_init();
}
float pre_last_err=0;
 float last_err=0;
 float Dis_Err0=0;
float Pre_Last_DeviationVar0=0;
float Last_DeviationVar0=0;
float Dis_Err00=0;
//void control_turn(float dev,float kp2,float kp1,float kd){
//	int16_t duty;
//	
//	Dis_Err0=(dev-last_err);
//		float tempa,tempb,tempc,max,min;//???????
//  //????,?????????
//  tempa=Pre_Last_DeviationVar0;
//  tempb=Last_DeviationVar0;
//  tempc=Dis_Err0;
//  max = tempa > tempb ? tempa:tempb;
//  max = max > tempc ? max:tempc;
//  min = tempa < tempb ? tempa:tempb;
//  min = min < tempc ? min:tempc;
//  if(tempa > min && tempa < max)    Dis_Err0 = tempa;
//  if(tempb > min  && tempb < max )  Dis_Err0 = tempb;
//  if(tempc > min  &&  tempc < max)  Dis_Err0 = tempc;
//  Pre_Last_DeviationVar0 = Last_DeviationVar0;
//  Last_DeviationVar0 = Dis_Err0;
//	Dis_Err0=Dis_Err00*0.5+Dis_Err0*0.5;
//	Dis_Err00=Dis_Err0;
//	
//	if(dev>0)
//		duty = (int)(dev*kp1+Dis_Err0*kd+dev*dev*kp2);
//	else
//		duty = (int)(dev*kp1+Dis_Err0*kd+dev*dev*-kp2);
//	pre_last_err=last_err;
//	last_err=dev;
//	if(duty>SERVO_LIMIT)duty = SERVO_LIMIT;
//	else if(duty<-SERVO_LIMIT)duty=-SERVO_LIMIT;
//	pwm_duty(SERVO_CH,SERVO_MID-duty);
//}
extern int16_t servo_pwm;
void control_turn(float dev,float kp2,float kp1,float kd){
	int16_t duty;
	Dis_Err0=(dev-last_err)*0.5+Dis_Err0*0.5;
	if(dev>0)
		duty = (int)(dev*kp1+Dis_Err0*kd+dev*dev*kp2);
	else
		duty = (int)(dev*kp1+Dis_Err0*kd+dev*dev*-kp2);
	last_err=dev;
	if(duty>SERVO_LIMIT)duty = SERVO_LIMIT;
	else if(duty<-SERVO_LIMIT)duty=-SERVO_LIMIT;
	servo_pwm = duty;
	pwm_duty(SERVO_CH,SERVO_MID-duty);
}

void control_run(int16_t duty){
//	duty = -duty;
	if(duty>0){
		pwm_duty(MOTOR_CH2,0);
		pwm_duty(MOTOR_CH1,duty);
	}else{
		pwm_duty(MOTOR_CH1,0);
		pwm_duty(MOTOR_CH2,duty);
	}
}


/**********************??????PID*************************************/

float aimspeed=0;


float Last_Err=0;
float Err=0;
float Expect=0;
float FeedBack=0;
float Dis_Err=0;
float Integrate=0;
float Control_OutPut=0;
float Control_OutPut_Limit=20000;
float Err_LPF=0;
float Last_Err_LPF=0;
float Dis_Err_LPF=0;
float Last_Dis_Err_LPF=0;
float Pre_Last_Dis_Err_LPF=0;
float Integrate_Max=16000;
int Kp=2600;
int Ki=30;
int Kd=200;
float Scale_Kp=1;
float Scale_Ki=0.1;
float Scale_Kd=1;

float PID_Control_Err_LPF(void)
{
	
//	Kp=params[0];
//	Ki=params[1];
//	Kd=params[2];
	
	  /*******????*********************/
  Last_Err=Err;//??????
  Err=Expect-FeedBack;//??????????
  Dis_Err=Err-Last_Err;//????

  Last_Err_LPF=Err_LPF;
  Err_LPF=0.7*Err+0.3* Last_Err;
  Dis_Err_LPF=Err_LPF-Last_Err_LPF;//???????????

	  /*******????*********************/
	//if(Err<100)
	{
     Integrate+=Scale_Ki*Ki*Err_LPF;
	}
	  /*******????*********************/

    if(Integrate>=Integrate_Max)
      Integrate=Integrate_Max;
    if(Integrate<=-Integrate_Max)
     Integrate=-Integrate_Max ;
		
  /*******?????*********************/
		
  Control_OutPut=Scale_Kp*Kp*Err_LPF//??
    +Integrate//??
      +Scale_Kd*Kd*Dis_Err_LPF;//??????,????????????
		
  /*******?????*********************/
		
  if(Control_OutPut>=Control_OutPut_Limit)
    Control_OutPut=Control_OutPut_Limit;
  if(Control_OutPut<=-Control_OutPut_Limit)
    Control_OutPut=-Control_OutPut_Limit;
	
  /*******?????*********************/
  return Control_OutPut;
}



/**************************????************************************/


float normalSpeed=40;
float minSpeed2=32;
float curveSpeed=35;
float speedK22=105;

uint16_t switchSpeedTop=1400;
uint16_t realSpeedTop=0;

//float normalSpeed=42;
//float minSpeed2=29;
//float curveSpeed=32;
//float speedK22=110;

//uint16_t switchSpeedTop=1100;
//uint16_t realSpeedTop=0;

extern float top;
float getaimspeed()
{
	
//	float aimSpeed = minSpeed2;
//	if(top>1800.0f)
//	realSpeedTop=1800.0f;
//	else realSpeedTop=top;
//	
//	  float referenceSpeed;
//    float minSpeed;
//    float speedK2;
//	
//	if(realSpeedTop >= switchSpeedTop)
//	{
//		referenceSpeed = normalSpeed;
//		
//	 minSpeed = curveSpeed;
//	//??: ??? - ???? * speedTop?YM?? / ??speedTop?YM??
//	aimSpeed = (referenceSpeed - (referenceSpeed - minSpeed) * (1800 - realSpeedTop) / (1800 - switchSpeedTop));
//	}
//	
//	else
// {
//		referenceSpeed = curveSpeed;

//		minSpeed = minSpeed2;
//		speedK2 = speedK22;
//		aimSpeed = (referenceSpeed - (referenceSpeed - minSpeed) *dev_k*100 * dev_k*100 / speedK2 / speedK2);
// }
// 
//	        /*?????*/
//        if (aimSpeed < minSpeed2)
//            aimSpeed = minSpeed2;
//        if (realSpeedTop >= switchSpeedTop && aimSpeed > normalSpeed)
//            aimSpeed = normalSpeed;
//        if (realSpeedTop < switchSpeedTop && aimSpeed > curveSpeed)
//            aimSpeed = curveSpeed;
    return 33;
			}

//float getaimspeed()
//{
//	float aimSpeed0 = 40;
// 	float aimSpeed1 = aimSpeed0-dev_k*20 ;
//	        /*?????*/
//        if (aimSpeed < minSpeed2)[
//            aimSpeed = minSpeed2;
//        if (realSpeedTop >= switchSpeedTop && aimSpeed > normalSpeed)
//            aimSpeed = normalSpeed;
//        if (realSpeedTop < switchSpeedTop && aimSpeed > curveSpeed)
//            aimSpeed = curveSpeed;
//    return aimSpeed1;
//}



float absf(float a)
{
	if(a>0)return a;
	else if(a<0)return -a;
	else return 0;
}


void Speed_control(void)
{

    /***************????****************/
    Expect=aimspeed;
    /***************????****************/
    FeedBack=-encoder_speed;
    /***************????***************/
    PID_Control_Err_LPF();
}


void Total_Control(void)
{
	Speed_control();
}