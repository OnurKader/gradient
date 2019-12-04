#include "color.c"

#include <getopt.h>
#include <signal.h>
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

void gradient(const short width, const short height, color_t* first, color_t* second)
{
	/* rgb2hsv(first); */
	/* rgb2hsv(second); */
	for(short row = 0; row < height; ++row)
	{
		for(short col = 0; col < width; ++col)
		{
			color_t color;
			color = hsvInterp(*first, *second, col, width);
			hsv2rgb(&color);
			setStr(&color);
			printf("%s ", color.str);
		}
		/* if(row != height - 1) */
		/* 	printf("\n"); */
		first->h = fmod((first->h + 0.018f), 360.f);
		second->h = fmod((second->h + 0.018f), 360.f);
	}
}

void signal_handle(int sig)
{
	printf("%d\b\033[?25h", sig);
	printf("\033[38;2m;\033[48;2m");
	exit(0);
}

int main(int argc, const char** argv)
{
	signal(SIGINT, signal_handle);
	signal(SIGTERM, signal_handle);

	color_t initial_color;
	color_t ending_color;
	initial_color.r = 229;
	initial_color.g = 13;
	initial_color.b = 217;
	ending_color.r = 20;
	ending_color.g = 206;
	ending_color.b = 241;

	rgb2hsv(&initial_color);
	rgb2hsv(&ending_color);
	printf("\033[?25l");
	short width, height;
	printf("\033[2J");
	uint8_t tick = 0U;

	while(1)
	{
		if((tick += 128U) > 0U)
			getTermSize(&width, &height);
		printf("\033[H");
		gradient(width, height, &initial_color, &ending_color);
		// 25 FPS
		usleep(40000U);
	}
	return 0;
}
