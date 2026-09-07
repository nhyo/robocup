/**
 * @file pwm.c
 * @brief simple pwm lib
 * @author TangSong404
 */
#include "pwm.h"

uint32_t PWM_CH[4] = {TIM_CHANNEL_1,TIM_CHANNEL_2,TIM_CHANNEL_3,TIM_CHANNEL_4};
uint16_t last_duty[4] = {0};

void pwm_init(void){
	for(uint8_t i = 0;i<PWM_CH_NUM;i++)
		HAL_TIM_PWM_Start(&PWM_TIM,PWM_CH[i]);
}

void pwm_duty(uint8_t ch,uint16_t duty){
	if(duty==last_duty[ch-1])return;
	if(duty>PWM_LIMIT_OUTPUT)duty = PWM_LIMIT_OUTPUT;
	__HAL_TIM_SET_COMPARE(&PWM_TIM, PWM_CH[ch-1],duty);
	last_duty[ch-1] = duty;
}
