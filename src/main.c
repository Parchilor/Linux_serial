#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "serial.h"

static struct {
	int fd;
	int slen;
	int rlen;
	char send_buf[256];
	char recv_buf[256];
} usart_args;

//#define usart_puts(format) printf(format)

#define MAX_CMD_LENGTH 256
#define MAX_CMD_ITEM 16

int usart_puts(const char* fmt, ...)
{
	va_list args;
	int len;
	char buff[128];

	va_start(args, fmt);
	len = vsnprintf((char*)buff, sizeof(buff), (char const*)fmt, args);
	va_end(args);

	buff[len] = '\n';
	UART_Send(usart_args.fd, buff, len);
	return len;
}


void usart_putc(char c)
{
	UART_Send(usart_args.fd, &c, 1);
}

char usart_getc(void)
{
	char c;
	UART_Recv(usart_args.fd, &c, 1);
	return c;
}

struct cmdline {
	int count;
	const char *params[MAX_CMD_ITEM];
};

static void parse_cmdline(char *in, struct cmdline* cmd)
{
	char *p_in = in;
	cmd->count = 0;
	while(*p_in)
	{
		switch (*p_in)
		{
			case '\r':
			case '\n':
			case ' ':
			case '\t':
				p_in++;
				continue;
		}
		if(0 == *p_in)
			break;
		cmd->params[cmd->count] = p_in;
		cmd->count++;
		
		while(*p_in)
		{
			if ('\r' == *p_in || '\n' == *p_in || ' ' == *p_in ||'\t' == *p_in)
			{
				*p_in = 0;
				p_in++;
				break;
			}
			p_in++;
		}
	}
}

static int get_cmd_buffer(char *buff, int len)
{
	char *p = buff;
	int ch;

	while(p - buff < len-1)
	{
		ch = usart_getc();
		if(ch >= 0)
		{
			if('\r' == ch || '\n' == ch)
			{
				break;
			}
			if('\b' == ch)
			{
				if(p > buff)
					p--;
			}
			else
			{
				*p++ = ch;
			}
			usart_putc(ch);
		}
	}
	*p = 0;
	return p - buff;
}

static void cmd_reset(struct cmdline* cmd)
{
	usart_puts("This is reset!\n");
}

static void cmd_pn (struct cmdline* cmd)
{
	if((cmd->count == 2) && (strcmp(cmd->params[1], "init") == 0))
	{
		usart_puts("init pannel io\n");
	}
	else
	{
		usart_puts("pn others!\n");
	}
}

static void cmd_help(struct cmdline *cmd);

const static struct _cmd_def {
	char *name;
	void (*proc)(struct cmdline*);
	char *help_msg;
} cmds[] = {
	{"help", cmd_help, "show this message"},
	{"reset", cmd_reset, "reset mcu"},
	{"pn", cmd_pn, "pannel"},
};

static void cmd_help(struct cmdline *cmd)
{
	int i;
	for(i = 0; i < sizeof(cmds)/sizeof(*cmds); i++)
	{
		usart_puts("\n%s ---> %s\n", cmds[i].name, cmds[i].help_msg);
	}
}

static void dispatch (struct cmdline *cmd)
{
	int i;
	if(!cmd->count)
		return ;
	for(i = 0; i < sizeof(cmds)/sizeof(*cmds); i++)
	{
		if(!strcmp(cmds[i].name, cmd->params[0]))
		{
//			usart_putc('\n');
			cmds[i].proc(cmd);
			return ;
		}
	}
}

static void usart_init(void)
{
	usart_args.fd = UART_Open(usart_args.fd, "/dev/ttyUSB0");
	if(usart_args.fd < 0)
	{
		return;
	}

	UART_Init(usart_args.fd, 115200, 0, 8, 1, 'N');
}

int main(int arcv, char *argv[])
{
	static char cmd_buffer[MAX_CMD_LENGTH];
	static struct cmdline cmd;
	usart_init();
	while(1){
		usart_puts("\nMach$ ");
		get_cmd_buffer(cmd_buffer, MAX_CMD_LENGTH);
		parse_cmdline(cmd_buffer, &cmd);
		dispatch(&cmd);
	}
	return 0;
}
