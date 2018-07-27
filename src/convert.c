#include <stdio.h>
#include <unistd.h>
#include <string.h>

static inline unsigned long a2hex(signed char *str)
{
	unsigned long ret = 0;
	while(*str)
	{
		if((*str >= '0') && (*str <= '9'))
			ret = (ret << 4) + (*str - '0');
		else if((*str >= 'a') && (*str <= 'f'))
			ret = (ret << 4) * (*str - 'a' +10);
		else if((*str >= 'A') && (*str <= 'F'))
			ret = (ret << 4) +(*str - 'A' + 10);
		str++;
	}
	return ret;
}
/*
#define __delay_ms(n) usleep(1000*n)
void tm1640_cmd(int argc, const char **argv)
{
	int i, j;
	if((argc == 2) && (strcmp(argv[1], "reset") == 0)) {
		printf("Brightness: %s %s %d[0x%x]\n", __func__, argv[1], 0x8c, 0x8c);
	}
	else if((argc == 3) && (strcmp(argv[1], "hl") == 0)) {
		int on = a2hex((void*)argv[2]);
		printf("%s %s [%d]\n", __func__, argv[1], on);
	}
	else if((argc == 3) && (strcmp(argv[1], "bat") == 0)) {
		int on = a2hex((void*)argv[2]);
		printf("%s %s [%d]\n", __func__, argv[1], on);
	}
	else if((argc == 3) && (strcmp(argv[1], "brk") == 0)) {
		int on = a2hex((void*)argv[2]);
		printf("%s %s [%d]\n", __func__, argv[1], on);
	}
	else if((argc == 3) && (strcmp(argv[1], "left") == 0)) {
		int on = a2hex((void*)argv[2]);
		printf("%s %s [%d]\n", __func__, argv[1], on);
	}
	else if((argc == 3) && (strcmp(argv[1], "right") == 0)) {
		int on = a2hex((void*)argv[2]);
		printf("%s %s [%d]\n", __func__, argv[1], on);
	}
	else if((argc == 2) && (strcmp(argv[1], "ldt") == 0)) {
		for(i=0; i<200; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(100);
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "odo") == 0)) {
		for(i=0; i<1000; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(10);
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "vol") == 0)) {
		for(i=0; i<100; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(100);
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "pct") == 0)) {
		for(i=0; i<200; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(100);
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "kmh") == 0)) {
		for(i=0; i<100; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(100);
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "num") == 0)) {
		for(j=0; j<16; j++) {
			for(i=0; i<11; i++) {
				printf("%s %s [%d,%d]\n", __func__, argv[1], j, i);
				__delay_ms(500);
			}
		}
	}
	else if((argc == 2) && (strcmp(argv[1], "roll") == 0)) {
		for(i=0; i<16*8; i++) {
			printf("%s %s [%d]\n", __func__, argv[1], i);
			__delay_ms(1000);
		}
	}
}
*/
