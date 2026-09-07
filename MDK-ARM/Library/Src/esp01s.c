/**
 * @file esp01s.c
 * @brief This file provides some simple functions with esp01s to bulid wifi connections (TCP,UDP)
 * @author TangSong404
 */
#include "esp01s.h"

FIFO esp_rxf;
FIFO esp_txf;
DMA_UART esp_dma_uart;
GPIO_TypeDef *ESP_Port;
uint16_t ESP_RST;
uint16_t ESP_EN;

#define ESP01_EN(x)                   ((x) ? (HAL_GPIO_WritePin(ESP_Port, ESP_RST, GPIO_PIN_SET))  : (HAL_GPIO_WritePin(ESP_Port, ESP_RST, GPIO_PIN_RESET)))
#define ESP01_RST(x)                   ((x) ? (HAL_GPIO_WritePin(ESP_Port, ESP_EN, GPIO_PIN_SET))  : (HAL_GPIO_WritePin(ESP_Port, ESP_EN, GPIO_PIN_RESET)))

uint8_t ATs[128];
static uint8_t esp01s_waitAck (char *wait_buffer){
    uint8_t return_state = ACK_TIMEOUT;
		uint32_t timeout = WAIT_TIME;
    char receiver_buffer[8] = {0,0,0,0,0,0,0,0};
    do
    {
        HAL_Delay(1);
        dma_uart_fifo_tail_peek(&esp_dma_uart, (uint8_t *)receiver_buffer, 8);
        if(strstr(receiver_buffer, wait_buffer))
        {
            return_state = ACK_OK;
            break;
        }
        else if(strstr(receiver_buffer, "ERROR"))
        {
            return_state = ACK_ERROR;
            break;
        }
    }while(timeout --);
    return return_state;
}
extern DMA_UART usb_dma_uart;
uint8_t esp01s_init(DMA_HandleTypeDef* dma,UART_HandleTypeDef *uart,GPIO_TypeDef *Port,uint16_t RST,uint16_t EN){
	ESP_Port = Port;
	ESP_RST = RST;
	ESP_EN = EN;
	
	ESP01_EN(1);
  ESP01_RST(0);
  HAL_Delay(10);
  ESP01_RST(1);
  HAL_Delay(500);
	
	dma_uart_init(&esp_dma_uart,dma,uart,&esp_txf,&esp_rxf);

	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CWAUTOCONN=0\r\n",17);
	uint8_t state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	
	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CWMODE=1\r\n",13);
	state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	
	return state;
}
uint8_t esp01s_wifi(const char* ssid,const char* password){
	
	memset(ATs,0,sizeof(ATs));
	dma_uart_fifo_clear(&esp_dma_uart);
  snprintf((char*)ATs, sizeof(ATs), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
  dma_uart_transmit(&esp_dma_uart,ATs,sizeof(ATs));
	uint8_t state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	
	return state;
}

uint8_t esp01s_udp(const char* ip,uint16_t port){
	
	dma_uart_fifo_clear(&esp_dma_uart);
	
	memset(ATs,0,sizeof(ATs));
  snprintf((char*)ATs, sizeof(ATs), "AT+CIPSTART=\"UDP\",\"%s\",%hu,8080\r\n", ip, port);
  dma_uart_transmit(&esp_dma_uart,ATs,sizeof(ATs));
  uint8_t state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;
	
	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CIPMODE=1\r\n",14);
	state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;

	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CIPSEND\r\n",12);
	state = esp01s_waitAck(">");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;
	
	return 0;
}

uint8_t esp01s_tcp_start(const char* ip,uint16_t port){
	
	dma_uart_fifo_clear(&esp_dma_uart);
	
	memset(ATs,0,sizeof(ATs));
  snprintf((char*)ATs, sizeof(ATs), "AT+CIPSTART=\"TCP\",\"%s\",%hu\r\n", ip, port);
	dma_uart_transmit(&esp_dma_uart,ATs,sizeof(ATs));
	uint8_t state = esp01s_waitAck("OK");
	if(state)return state;
	
	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CIPMODE=1\r\n",14);
	state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;

	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CIPSEND\r\n",12);
	state = esp01s_waitAck(">");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;
	return 0;
}

uint8_t esp01s_tcp_end(void){
	
	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"+++",3);
	dma_uart_fifo_clear(&esp_dma_uart);
	
	dma_uart_transmit(&esp_dma_uart,(uint8_t*)"AT+CIPCLOSE=1\r\n",15);
	uint8_t state = esp01s_waitAck("OK");
	dma_uart_fifo_clear(&esp_dma_uart);
	if(state)return state;

	return 0;
}

void esp01s_send(uint8_t *pData,uint16_t Size){
	dma_uart_transmit(&esp_dma_uart,pData,Size);
}

void esp01s_send_discard(){
	dma_uart_transmit_discard(&esp_dma_uart);
}

uint16_t esp01s_receive(uint8_t *pData,uint16_t len){
	return dma_uart_fifo_read(&esp_dma_uart,pData,len);
}

uint16_t esp01s_peek(uint8_t *pData,uint16_t len){
	return dma_uart_fifo_tail_peek(&esp_dma_uart,pData,len);
}

void esp01s_callback_Rx(UART_HandleTypeDef *uart,uint16_t Size){
	dma_uart_callback_Rx(&esp_dma_uart,uart,Size);
}

void esp01s_callback_Tx(UART_HandleTypeDef *uart){
	dma_uart_callback_Tx(&esp_dma_uart,uart);
}
