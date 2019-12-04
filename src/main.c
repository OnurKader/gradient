#include "color.c"

#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <term.h>
#include <unistd.h>

void display_inputs(int);

void getTermSize(short* width, short* height)
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	*width = size.ws_col;
	*height = size.ws_row;
}

void gradient(const short width, const short height, color_t* first, color_t* second)
{
	for(short row = 0; row < height; ++row)
	{
		for(short col = 0; col < width; ++col)
		{
			color_t color = hsvInterp(*first, *second, col, width);
			hsv2rgb(&color);
			setStr(&color);
			printf("%s ", color.str);
		}
		first->h = fmod((first->h + 0.018f), 360.f);
		second->h = fmod((second->h + 0.018f), 360.f);
	}
}

void signal_handle(int sig)
{
	printf("%d\b\033[?25h", sig);
	printf("\033[38;2m;\033[48;2m\n");
	display_inputs(1);
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
	printf("\033[2J");
	uint8_t tick = 0U;

	short width, height;
	getTermSize(&width, &height);
	short initial_width = width;
	short initial_height = height;
	display_inputs(0);
	while(1)
	{
		if((tick += 128U) > 0U)
		{
			getTermSize(&width, &height);
			if(initial_width != width || initial_height != height)
			{
				initial_height = height;
				initial_width = width;
				printf("\033[2J");
			}
		}
		printf("\033[H");
		gradient(width, height, &initial_color, &ending_color);
		// 25 FPS
		usleep(40000U);
	}
	return 0;
}

void display_inputs(
	int display)	// Credit to
					// "https://www.reddit.com/r/C_Programming/comments/64524q/turning_off_echo_in_terminal_using_c/dfzso9b?utm_source=share&utm_medium=web2x"
{
	struct termios t;

	/* Get console mode */
	errno = 0;
	if(tcgetattr(STDIN_FILENO, &t))
	{
		fprintf(stderr, "tcgetattr failed (%d)\n", errno);
		return;
	}

	/* Set console mode to echo or no echo */
	if(display)
	{
		t.c_lflag |= ECHO;
	}
	else
	{
		t.c_lflag &= ~((tcflag_t)ECHO);
	}
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &t))
	{
		fprintf(stderr, "tcsetattr failed (%d)\n", errno);
		return;
	}
}
