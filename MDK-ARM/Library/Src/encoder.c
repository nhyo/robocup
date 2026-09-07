/**
 * @file encoder.c
 * @brief This file provides simple funcs with AB phase incremental magnetic Hall sensor to get rotate speed
 * @author TangSong404
 */
#include "encoder.h"
uint16_t encoder_local = 0;
int encoder_speed = 0;
uint8_t enc_times = 0;
void encoder_init(void){
	HAL_TIM_Encoder_Start(&ENC_TIM, TIM_CHANNEL_ALL);
}

void encoder_get(void){
    uint16_t temp = __HAL_TIM_GET_COUNTER(&ENC_TIM);
    int16_t diff = temp - encoder_local;

    if (diff > (int16_t)((ENC_TIM).Init.Period / 2)) {
        encoder_speed = diff - (ENC_TIM).Init.Period - 1;
    } else if (diff < -(int16_t)((ENC_TIM).Init.Period / 2)) {
        encoder_speed = diff + (ENC_TIM).Init.Period + 1;
    } else {
        encoder_speed = diff;
    }

    encoder_local = temp;
}
