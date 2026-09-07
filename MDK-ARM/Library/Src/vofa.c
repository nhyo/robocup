/**
 * @file vofa.c
 * @brief vofa plus with esp01s wifi module
 * @author TangSong404
 */
 
#include "vofa.h"
float params[MAX_CH_NUM] = {0};

uint8_t vofa_init(void){
	if(esp01s_init(&ESP_DMA,&ESP_UART,ESP_Port,ESP_RST_PIN,ESP_EN_PIN))return 0;
	if(esp01s_wifi(SSID,PASSWORD))return 0;
	if(esp01s_udp(REMOTE_IP,REMOTE_PORT))return 0;
	esp01s_send((uint8_t*)"The udp connection has been established!\r\n",42);
	return 1;
}

void vofa_justfloat(uint8_t channels, ...) {
	
  if (channels <= 0||channels>MAX_CH_NUM) {
    return;
  }
  va_list args;
  va_start(args, channels);
	uint8_t tail = channels*sizeof(float);
  uint8_t data_bytes[tail+4]; 
  for (uint8_t i = 0; i < channels; i++) {
    float data = va_arg(args, double);
    memcpy(data_bytes + i * sizeof(float), &data, sizeof(float));
  }
	data_bytes[tail] = 0x00;
	data_bytes[tail+1] = 0x00;
	data_bytes[tail+2] = 0x80;
	data_bytes[tail+3] = 0x7f;
  va_end(args); 
  esp01s_send(data_bytes, channels * sizeof(float)+4);
}

void vofa_rawdata(uint8_t* pData,uint16_t len){
	esp01s_send(pData,len);
}

void vofa_firewater(const char *format, ...){
	char buffer[128];
	va_list args;
	va_start(args, format);
	uint16_t length = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	esp01s_send((uint8_t*)buffer,length);
}
void vofa_parameters(void){
	char end[9] = {0};
	end[8] = '\0';
	char temp[128] = {0};
	char* ptr = temp;
	int index = 0;
	float data = 0.0f;
	esp01s_peek((uint8_t*)end,sizeof(end)-1);
	if(!strcmp(end,"params\r\n")){
		esp01s_receive((uint8_t*)temp,sizeof(temp));
		while(sscanf(ptr,"%d-%f\n", &index,&data)==2){
			if(index<MAX_CH_NUM){
				params[index] = data;
#if PARAM_ECHO
				vofa_firewater("param %d set %f!\n",index,data);
#endif
			}
#if PARAM_ECHO
			else
				vofa_firewater("param %d out of range!\n",index);
#endif			
			ptr = strchr(ptr, '\n');
			if (ptr == NULL)break;
			ptr++;
		}
	}
}

uint8_t vofa_signal(const char* signal){
	char end[10] = {0};
	uint8_t num = esp01s_peek((uint8_t*)end,sizeof(end)-1);
	if(!num)return 0;
	if(strstr(end,signal)){
		esp01s_receive((uint8_t*)end,10);
		return 1;
	}
	return 0;
}
