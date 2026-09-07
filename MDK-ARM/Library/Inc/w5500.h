#ifndef W5500_H
#define W5500_H
#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define W5500_SPI hspi1

#define W5500_RST GPIO_PIN_12
#define W5500_CS GPIO_PIN_13
#define W5500_PORT GPIOB

//network config
#define Sn_TXMEM_SIZE(ch)               (0x001F08 + (ch<<5))
#define Sn_RXMEM_SIZE(ch)               (0x001E08 + (ch<<5))
#define SHAR                       (0x000900)
#define SUBR                       (0x000500)
#define GATE                       (0x000100)
#define SIPR                       (0x000F00)
#define RTR0                        (0x001900)
#define RTR1                        (0x001A00)
#define WIZ_RCR                         (0x001B00)
//socket config
#define Sn_MR(ch)                       (0x000008 + (ch<<5))
#define Sn_RX_RD0(ch)                   (0x002808 + (ch<<5))
#define Sn_RX_RD1(ch)                   (0x002908 + (ch<<5))
#define Sn_CR(ch)                       (0x000108 + (ch<<5))
#define Sn_SR(ch)                       (0x000308 + (ch<<5))
#define Sn_PORT0(ch)                    (0x000408 + (ch<<5))
#define Sn_PORT1(ch)                    (0x000508 + (ch<<5))
#define Sn_RX_RSR0(ch)                  (0x002608 + (ch<<5))
#define Sn_RX_RSR1(ch)                  (0x002708 + (ch<<5))
#define Sn_MR_UDP                    0x02
#define Sn_CR_RECV                   0x40
#define Sn_CR_CLOSE                  0x10
#define Sn_CR_OPEN                   0x01
#define SOCK_UDP                     0x22
#define SOCK_CLOSE                    0x00

typedef void (*PARSE_FUNC)(uint8_t*);

void w5500_init(void);
void w5500_udp_statemachine(uint8_t s,uint16_t set_len,PARSE_FUNC func);

#endif
