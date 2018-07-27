#ifndef __SERIAL_H_
#define __SERIAL_H_
//#define	MSG_TEST

int UART_Open(int, char*);
void UART_Close();
int UART_Init(int, int, int, int, int, int);
int UART_Recv(int, char*, int);
int UART_Send(int, char*, int);
#endif
