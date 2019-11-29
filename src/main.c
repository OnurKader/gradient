#include "color.c"
#include "utils.c"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void getTermSize(short* width, short* height)
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	*width = size.ws_col;
	*height = size.ws_row;
}

void gradient(const short width, const short height) {}

int main(int argc, const char** argv)
{
	short width, height;
	getTermSize(&width, &height);
	gradient(width, height);
	color_t temp;
	temp.r = 202;
	temp.g = 101;
	temp.b = 154;
	rgb2hsv(&temp);
	printf("H:%d\nS:%d\nV:%d\n", temp.h, temp.s, temp.v);
	hsv2rgb(&temp);
	printf("R:%d\nG:%d\nB:%d\n", temp.r, temp.g, temp.b);
	return 0;
}
