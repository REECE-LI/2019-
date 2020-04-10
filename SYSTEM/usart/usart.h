#ifndef __UART_H_
#define __UART_H_

#include "stm32f10x.h"
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
void uart_init(u32 baudRate);
void PutChar(u8 Data);
void PutNChar(u8 *buf , u16 size);
void PutStr(char *str);
#endif
