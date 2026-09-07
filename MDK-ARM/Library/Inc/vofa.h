#ifndef ZF_ASSISTANT_H
#define ZF_ASSISTANT_H
#include "esp01s.h"
#include "stdarg.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
#define ESP_UART huart1
#define ESP_DMA hdma_usart1_rx

#define SSID "YOUR_WIFI_SSID" // Replace with your Wi-Fi SSID
#define PASSWORD "nhyo" // Replace with your Wi-Fi password
#define REMOTE_IP "192.168.1.100" // Replace with the receiver IP address
#define REMOTE_PORT 8082

#define ESP_Port GPIOA
#define ESP_EN_PIN GPIO_PIN_8
#define ESP_RST_PIN GPIO_PIN_11

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#define MAX_CH_NUM 10
#define PARAM_ECHO 0

uint8_t vofa_init(void);
void vofa_justfloat(uint8_t channels, ...);
void vofa_rawdata(uint8_t* pData,uint16_t len);
void vofa_firewater(const char *format, ...);
void vofa_parameters(void);
uint8_t vofa_signal(const char* signal);
extern float params[MAX_CH_NUM];

#endif
