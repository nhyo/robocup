#ifndef PWM_H
#define PWM_H
#include "main.h"

extern TIM_HandleTypeDef htim4;
#define PWM_TIM htim4

#define PWM_CH_NUM 3
#define PWM_LIMIT_OUTPUT 20000

void pwm_init(void);
void pwm_duty(uint8_t ch,uint16_t duty);

#endif

