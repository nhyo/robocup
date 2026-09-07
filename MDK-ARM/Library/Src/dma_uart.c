/**
 * @file dma_uart.c
 * @brief This file provides some dma uart functions to use
 * @author TangSong404
 */
#include "dma_uart.h"
#include "Dev.h"

void dma_uart_receive_start(DMA_UART *dma_uart){
	HAL_UARTEx_ReceiveToIdle_DMA(dma_uart->uart,dma_uart->rx_Buffer,sizeof(dma_uart->rx_Buffer));
	__HAL_DMA_DISABLE_IT(dma_uart->dma,DMA_IT_HT);
}

void dma_uart_init(DMA_UART *dma_uart,DMA_HandleTypeDef* dma,UART_HandleTypeDef *uart,FIFO* txf,FIFO* rxf){
	dma_uart->uart = uart;
	dma_uart->dma = dma;
	dma_uart->txCplt = 1;
	fifo_init(rxf);
	fifo_init(txf);
	dma_uart->rx_fifo = rxf;
	dma_uart->tx_fifo = txf;
	dma_uart_receive_start(dma_uart);
}

void dma_uart_transmit(DMA_UART *dma_uart,uint8_t *pData,uint16_t Size){
	if(!Size)return;
	fifo_write(dma_uart->tx_fifo,pData,Size);
	if(dma_uart->txCplt){
		dma_uart->txCplt = 0;
		dma_uart_callback_Tx(dma_uart,dma_uart->uart);
	}
}
#define GO 1
#include "Deploy.h"
extern int circle_time;
extern float top;
extern int time_unix;
extern int encoder_speed;
extern float aimspeed;
extern uint16_t l_block_cnt;
extern uint16_t r_block_cnt;
void dma_uart_transmit_discard(DMA_UART *dma_uart){
	if(dma_uart->txCplt){
			dma_uart->txCplt = 0;
			uint16_t lenf = 9;
			uint16_t len1 = (uint16_t)(int)(l_num);
			uint16_t len2 = (uint16_t)(int)(r_num); 
			uint16_t len3 = (uint16_t)(int)(M_num); 
			float fdatas[9] = {dev0,dev_k,dev_b,track_width,l_num,r_num,w1,(float)(int)l_block_cnt,(float)(int)encoder_speed};
			
			fifo_write(dma_uart->tx_fifo,(uint8_t*)&lenf,sizeof(uint16_t));
			fifo_write(dma_uart->tx_fifo,(uint8_t*)fdatas,sizeof(float)*9);
			
#if GO
			fifo_write(dma_uart->tx_fifo,(uint8_t*)&len1,sizeof(uint16_t));
			fifo_write(dma_uart->tx_fifo,(uint8_t*)L_point2,sizeof(PointData_Send)*(l_num));
		
			fifo_write(dma_uart->tx_fifo,(uint8_t*)&len2,sizeof(uint16_t));
			fifo_write(dma_uart->tx_fifo,(uint8_t*)R_point2,sizeof(PointData_Send)*(r_num));
		
			fifo_write(dma_uart->tx_fifo,(uint8_t*)&len3,sizeof(uint16_t));
			fifo_write(dma_uart->tx_fifo,(uint8_t*)M_point2,sizeof(PointData_Send)*M_num);
#else
		uint16_t num = 0;
		fifo_write(dma_uart->tx_fifo,(uint8_t*)&num,sizeof(uint16_t));
		fifo_write(dma_uart->tx_fifo,(uint8_t*)Dataprocess_send,sizeof(PointData_Send)*num);
#endif
		

			fifo_write(dma_uart->tx_fifo,(uint8_t*)"[end]",5);
			dma_uart_callback_Tx(dma_uart,dma_uart->uart);
		}
}

uint16_t dma_uart_fifo_tail_peek(DMA_UART *dma_uart,uint8_t* array,uint16_t len){
	return fifo_tail_peek(dma_uart->rx_fifo,array,len);
}

uint16_t dma_uart_fifo_read(DMA_UART *dma_uart,uint8_t* array,uint16_t len){
	return fifo_read(dma_uart->rx_fifo,array,len);
}

void dma_uart_fifo_clear(DMA_UART *dma_uart){
	fifo_clear(dma_uart->rx_fifo);
}

void dma_uart_callback_Rx(DMA_UART *dma_uart,UART_HandleTypeDef *uart,uint16_t Size){
	if(dma_uart->uart->Instance == uart->Instance){
		fifo_write(dma_uart->rx_fifo,dma_uart->rx_Buffer,Size);
		dma_uart_receive_start(dma_uart);
	}
}

void dma_uart_callback_Tx(DMA_UART *dma_uart,UART_HandleTypeDef *uart){
	if(dma_uart->uart->Instance == uart->Instance){
		uint8_t r = fifo_read(dma_uart->tx_fifo,dma_uart->tx_Buffer,TX_BUF_SIZE);
		if(r)HAL_UART_Transmit_DMA(dma_uart->uart,dma_uart->tx_Buffer,r);
		else dma_uart->txCplt = 1;
	}
}
