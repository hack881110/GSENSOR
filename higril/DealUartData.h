#ifndef _DEAL_UART_DATA
#define _DEAL_UART_DATA

#include "common.h"
#include "Serial.h"


extern float  yaw;  //偏航角
extern float  pitch;//俯仰
extern float  roll; //滚转

extern int k1;
extern int k2;
extern int k3;

#define RX_BUFFER_SIZE 1024 //接收缓冲区字节数

extern CHAR Rx_buffer[RX_BUFFER_SIZE]; //接收数据缓冲区

extern CHAR *pHeadofRx_Buffer;
extern CHAR *pTailofRx_Buffer;
extern short iEndFlag0fRx_Buffer;


extern bool Check_Data_Invalid();
extern int iAscToBcd(char *pcASC,char *pcBCD,int iLength);
extern void VS_StrTrim(char*pStr);
extern unsigned char Sum_check(char* rx_buffer);
extern void UART2_Get_IMU(char *rx_buffer);
//extern void UART2_Get_Motion();
#endif