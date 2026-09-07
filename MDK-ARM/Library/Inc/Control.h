#ifndef CONTROL_H
#define CONTROL_H
#include "pwm.h"
#include "main.h"
#include "encoder.h"

#define SERVO_MID 983

#define SERVO_LIMIT 180

#define SERVO_CH 1
#define MOTOR_CH1 2
#define MOTOR_CH2 3

#define MOTOR_LIMIT 19999

void control_init(void);
void control_turn(float dev,float kp2,float kp1,float kd);
void control_run(int16_t duty);
void control_run_velo(int speed,float kp,float ki,float kd);
void Total_Control(void);
void Speed_control(void);
float absf(float a);
float getaimspeed();
extern float Control_OutPut;
extern float aimspeed;
#endif