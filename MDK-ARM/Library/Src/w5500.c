/**
 * @file w5500.c
 * @brief This file provides method to use bulid a udp connect between stm32 and another device
 * @author TangSong404
 */
#include "w5500.h"

#define W5500_RST_H HAL_GPIO_WritePin(W5500_PORT, W5500_RST, GPIO_PIN_SET);
#define W5500_RST_L HAL_GPIO_WritePin(W5500_PORT, W5500_RST, GPIO_PIN_RESET);
#define W5500_CS_H HAL_GPIO_WritePin(W5500_PORT, W5500_CS, GPIO_PIN_SET);
#define W5500_CS_L HAL_GPIO_WritePin(W5500_PORT, W5500_CS, GPIO_PIN_RESET);

uint8_t W5500_MAC[6]={0x02, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t W5500_LIP[4]={192, 168, 1, 10};
uint8_t W5500_SUB[4]={255,255,255,0};
uint8_t W5500_GW[4]={192, 168, 1, 1};
#define W5500_TIMEOUT 2000
#define W5500_RETRY 3
const uint8_t tx_soc[8] = {16 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
const uint8_t rx_soc[8] = {16 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
uint8_t w5500_buffer[2000];

uint8_t W5500_RIP[4]={192, 168, 1, 100};	
uint16_t W5500_RPORT = 8082;
uint16_t W5500_LPORT = 8080;

void w5500_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len)
{
		addrbsb|=0x04;
		uint8_t data[3]={
			(uint8_t) ((addrbsb & 0x00FF0000)>>16),
			(uint8_t) ((addrbsb & 0x0000FF00)>> 8),
			(uint8_t) ((addrbsb & 0x000000FF)>> 0),
		};
		W5500_CS_L;
		HAL_SPI_Transmit(&W5500_SPI,data,3,100);
		HAL_SPI_Transmit(&W5500_SPI,buf,len,100);
		W5500_CS_H;
}

void w5500_write_byte(uint32_t addrbsb,uint8_t da)
{
		addrbsb|=0x04;
		uint8_t data[3]={
			(uint8_t) ((addrbsb & 0x00FF0000)>>16),
			(uint8_t) ((addrbsb & 0x0000FF00)>> 8),
			(uint8_t) ((addrbsb & 0x000000FF)>> 0),
		};
		W5500_CS_L;
		HAL_SPI_Transmit(&W5500_SPI,data,3,100);
		uint8_t temp = da;
		HAL_SPI_Transmit(&W5500_SPI,&temp,1,100);
		W5500_CS_H;
}

void w5500_read_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len){
		uint8_t data[3]={
			(uint8_t) ((addrbsb & 0x00FF0000)>>16),
			(uint8_t) ((addrbsb & 0x0000FF00)>> 8),
			(uint8_t) ((addrbsb & 0x000000F8)),
		};
		W5500_CS_L;
		HAL_SPI_Transmit(&W5500_SPI,data,3,100);
		uint8_t null = 0x00;
		for(uint16_t i = 0;i<len;i++)
			HAL_SPI_TransmitReceive(&W5500_SPI,&null,buf+i,1,100);
		W5500_CS_H;
}

uint8_t w5500_read_byte(uint32_t addrbsb){
		uint8_t data[3]={
			(uint8_t) ((addrbsb & 0x00FF0000)>>16),
			(uint8_t) ((addrbsb & 0x0000FF00)>> 8),
			(uint8_t) ((addrbsb & 0x000000F8))
		};
		W5500_CS_L;
		HAL_SPI_Transmit(&W5500_SPI,data,3,100);
		uint8_t temp;
		uint8_t null = 0x00;
		HAL_SPI_TransmitReceive(&W5500_SPI,&null,&temp,1,100);
		W5500_CS_H;
		return temp;
}

void w5500_init(void){
	W5500_RST_L;
  HAL_Delay(5);  
  W5500_RST_H;
  HAL_Delay(100); 
	
	w5500_write_buf(SHAR,W5500_MAC,6);
	w5500_write_buf(SUBR,W5500_SUB,4);
	w5500_write_buf(GATE,W5500_GW,4);
	w5500_write_buf(SIPR,W5500_LIP,4);
	
	for (uint8_t i = 0 ; i < 8; i++){
		w5500_write_byte((Sn_TXMEM_SIZE(i)), tx_soc[i]);
    w5500_write_byte((Sn_RXMEM_SIZE(i)), rx_soc[i]);
	}
	w5500_write_byte(RTR0,(uint8_t)((W5500_TIMEOUT & 0xff00) >> 8));
  w5500_write_byte(RTR1,(uint8_t)(W5500_TIMEOUT & 0x00ff));
	w5500_write_byte(WIZ_RCR,W5500_RETRY);
}

void w5500_socket_close(uint8_t s)
{
   w5500_write_byte( Sn_CR(s) ,Sn_CR_CLOSE);
   while( w5500_read_byte(Sn_CR(s)));
}

uint8_t w5500_socket_open(uint8_t s, uint8_t protocol, uint16_t port, uint8_t flag)
{
   if ((protocol&0x0F)>=0x01&&(protocol&0x0F)<=0x05){
      w5500_socket_close(s);
      w5500_write_byte(Sn_MR(s) ,protocol | flag);
      w5500_write_byte( Sn_PORT0(s) ,(uint8_t)((port & 0xff00) >> 8));
      w5500_write_byte( Sn_PORT1(s) ,(uint8_t)(port & 0x00ff));
      w5500_write_byte(Sn_CR(s) ,Sn_CR_OPEN);
      while( w5500_read_byte(Sn_CR(s)) );
      return 1;
   }
   return 0;
}

uint16_t w5500_udp_getsize(uint8_t s){
  uint16_t val=0,val1=0;
  do
  {
    val1 = w5500_read_byte(Sn_RX_RSR0(s));
    val1 = (val1 << 8) + w5500_read_byte(Sn_RX_RSR1(s));
    if(val1 != 0)
    {
        val = w5500_read_byte(Sn_RX_RSR0(s));
        val = (val << 8) + w5500_read_byte(Sn_RX_RSR1(s));
    }
  } while (val != val1);
   return val;
}

uint16_t w5500_udp_recv(uint8_t s, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t *port)
{
   uint8_t head[8];
   uint16_t data_len=0;
   uint16_t ptr=0;
   uint32_t addrbsb =0;
   if ( len > 0 )
   {
      ptr = w5500_read_byte(Sn_RX_RD0(s));
      ptr = ((ptr & 0x00ff) << 8) + w5500_read_byte(Sn_RX_RD1(s));
      addrbsb = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;
      if ((w5500_read_byte(Sn_MR(s)) & 0x07)==Sn_MR_UDP)
      {
        w5500_read_buf(addrbsb, head, 0x08);        
        ptr += 8;
        addr[0]  = head[0];
        addr[1]  = head[1];
        addr[2]  = head[2];
        addr[3]  = head[3];
        *port    = head[4];
        *port    = (*port << 8) + head[5];
        data_len = head[6];
        data_len = (data_len << 8) + head[7];
        addrbsb = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;
        w5500_read_buf(addrbsb, buf, data_len);                
        ptr += data_len;
        w5500_write_byte( Sn_RX_RD0(s), (uint8_t)((ptr & 0xff00) >> 8));
        w5500_write_byte( Sn_RX_RD1(s), (uint8_t)(ptr & 0x00ff));
      }
      w5500_write_byte( Sn_CR(s) ,Sn_CR_RECV);
      while( w5500_read_byte( Sn_CR(s)) ) ;
   }
   return data_len;
}


void w5500_udp_statemachine(uint8_t s,uint16_t set_len,PARSE_FUNC func){
	switch (w5500_read_byte(Sn_SR(s))){
		case SOCK_UDP:{
			uint16_t len = w5500_udp_getsize(s);
			len = w5500_udp_recv(s,w5500_buffer,len,W5500_RIP,&W5500_RPORT);
			if(len==set_len)func(w5500_buffer);
			break;
		}
		case SOCK_CLOSE:{
			w5500_socket_open(s,Sn_MR_UDP,W5500_LPORT,0);
			break;
		}
		default:break;
	}
}
