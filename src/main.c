#include "color.c"

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

void gradient(const short width, const short height, color_t* first, color_t* second)
{
	rgb2hsv(first);
	rgb2hsv(second);
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
		printf("\n");
		first->h = fmod((first->h + 1.f), 360.f);
		second->h = fmod((second->h + 1.f), 360.f);
	}
	printf("%s", RESET);
}

int main(int argc, const char** argv)
{
	color_t initial_color;
	color_t ending_color;
	initial_color.r = 229;
	initial_color.g = 13;
	initial_color.b = 217;
	ending_color.r = 20;
	ending_color.g = 206;
	ending_color.b = 241;

	short width, height;
	getTermSize(&width, &height);
	gradient(width, height, &initial_color, &ending_color);
	return 0;
}
