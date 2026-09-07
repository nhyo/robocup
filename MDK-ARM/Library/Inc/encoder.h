#ifndef ENCODER_H
#define ENCODER_H
#include "main.h"

extern TIM_HandleTypeDef htim3;
#define ENC_TIM htim3

extern TIM_HandleTypeDef htim1;
#define ENC_GET_TIM htim1

void encoder_init(void);
void encoder_get(void);
void encoder_callback(void);

extern int encoder_speed;
extern uint16_t encoder_local;

#endif
