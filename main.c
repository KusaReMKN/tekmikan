#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mikanchan.c"

#define TEK_WIDTH	1024
#define TEK_HEIGHT	779

static void	clearTek(void);
static void	dotTek(int x, int y);
static void	enterTek(void);
static void	exitTek(void);
static void	lineTek(int x1, int y1, int x2, int y2, int mode);

int
main(int argc, char *argv[])
{
	int start, end;

	setbuf(stdout, NULL);
	enterTek();
	clearTek();

	start = end = -1;
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			int c = dat[(500 * i + j) * 4];
			if (j & 1)
				c >>= 4;
			if (!c && start == -1)
				start = i * 500 + j;
			if (c && start != -1) {
				int a = start % 500;
				int b = start / 500;
				lineTek(262+a, 700-b, 262+j-1, 700-i, '`');
				start = -1;
			}
		}
		if (start != -1) {
			int a = start % 500;
			int b = start / 500;
			lineTek(262+a, 700-b, 262+499, 700-i, '`');
			start = -1;
		}
	}
	fputs("\r\n\r\n\r\n\r\n", stdout);
	fputs("                   ", stdout);
	fputs("Mikan-chan is always watching you...", stdout);
	exitTek();

	return 0;
}

static void
clearTek(void)
{
	fputs("\033\014", stdout);
}

static void
dotTek(int x, int y)
{
	lineTek(x, y, x, y, '`');
}

static void
enterTek(void)
{
	fputs("\033[?38h", stdout);
	atexit(exitTek);
}

static void
exitTek(void)
{
	fputs("\033\003", stdout);
}

static void
lineTek(int x1, int y1, int x2, int y2, int mode)
{
	fputs("\035\033", stdout);
	fputc(mode, stdout);
	fputc(y1 >> 5 & 0x1F | 0x20, stdout);
	fputc(y1 >> 0 & 0x1F | 0x60, stdout);
	fputc(x1 >> 5 & 0x1F | 0x20, stdout);
	fputc(x1 >> 0 & 0x1F | 0x40, stdout);
	fputc(y2 >> 5 & 0x1F | 0x20, stdout);
	fputc(y2 >> 0 & 0x1F | 0x60, stdout);
	fputc(x2 >> 5 & 0x1F | 0x20, stdout);
	fputc(x2 >> 0 & 0x1F | 0x40, stdout);
	fputc(037, stdout);
}
