#include <stdio.h>
#include "serial.h"
#include <pthread.h>
#include <unistd.h>

#define RECV_LEN 126

int uart_fd = 0;

int func_recv(void * arg)
{
	char recv[RECV_LEN];
	while(1)
	{
		if(UART_Recv(uart_fd, recv, RECV_LEN))
			printf("%s", recv);
		usleep(400 * 1000);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	printf("Module: Testing!\n");
	uart_fd = UART_Open(uart_fd, "/dev/ttyUSB0");
	if(uart_fd < 0)
	{
		return -1;
	}

	UART_Init(uart_fd, 115200, 0, 8, 1, 'N');

	UART_Send(uart_fd, "i2c write 68 6b 0\n", 18);
	UART_Send(uart_fd, "i2c write 68 19 7\n", 18);
	UART_Send(uart_fd, "i2c write 68 1a 6\n", 18);
	UART_Send(uart_fd, "i2c write 68 1b 18\n", 19);
	UART_Send(uart_fd, "i2c write 68 1c 18\n", 19);

	pthread_t recvid;
	pthread_create(&recvid, NULL, func_recv, NULL);


	while(1)
	{
		UART_Send(uart_fd, "i2c read 68 47 2\n", 17);
		usleep(200 * 1000);
	}

	pthread_join(recvid, NULL);
	return 0;
}
