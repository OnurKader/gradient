#include "color.c"

#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <term.h>
#include <unistd.h>

// Terminal size
short t_width = 80, t_height = 32;
// Gradient Buffer
char* grad_buffer = NULL;

void display_inputs(int);

void getTermSize(short* width, short* height)
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	*width = size.ws_col;
	*height = size.ws_row;
}

void cls(void) { printf("\033[3J\033[H"); }

unsigned long long frame_count = 0ULL;

void gradient(short width, short height, color_t* first, color_t* second)
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
		first->h = fmod((first->h + 0.01f), 360.f);
		second->h = fmod((second->h + 0.01f), 360.f);
	}
}

void signal_int(int sig)
{
	printf("%d\b\033[?25h", sig);
	printf("\033[38;2m;\033[48;2m\n");
	display_inputs(1);
	free(grad_buffer);
	exit(0);
}

void signal_resize(int sig)
{
	if(sig == SIGWINCH)
	{
		cls();
		getTermSize(&t_width, &t_height);
	}
}

void substr(const char* src, char* dest, size_t start, size_t len)
{
	size_t n = 0LLU;
	while(n < len)
	{
		dest[n] = src[start + n];
		++n;
	}
}

int xx2int(const char* hex)
{
	char* endptr;
	int res = strtol(hex, &endptr, 16);
	if(endptr == hex)
		return -1;

	return res;
}

void setColors(int argc, const char** argv, color_t* init, color_t* end)
{
	switch(argc)
	{
		case 1:
			init->r = 229;
			init->g = 13;
			init->b = 217;
			end->r = 20;
			end->g = 206;
			end->b = 241;
			break;
		case 3:	   // check for the type of hex, #FF012A - 0x99FAFA - BBA022 or maybe
				   // rgb(123, 234, 41)
			if(index(argv[1], '#') && index(argv[2], '#'))
			{
				// #RRGGBB #F2F0C8
				char* temp = malloc(4);

				substr(argv[1], temp, 1, 2);
				init->r = xx2int(temp);
				substr(argv[1], temp, 3, 2);
				init->g = xx2int(temp);
				substr(argv[1], temp, 5, 2);
				init->b = xx2int(temp);

				substr(argv[2], temp, 1, 2);
				end->r = xx2int(temp);
				substr(argv[2], temp, 3, 2);
				end->g = xx2int(temp);
				substr(argv[2], temp, 5, 2);
				end->b = xx2int(temp);

				free(temp);
			}
			else if(*argv[1] == 'r' && *argv[2] == 'r')
			{
				// rgb(r,g,b) and with spaces rgb(r, g, b); Somehow just find the comma and
				// go to the next non space? Maybe sscanf
			}
			else
			{
				fprintf(stderr,
						"\t\033[31;1mWrong Type of Arguments%s\n\t#RRGGBB or "
						"rgb(R,G,B)\n",
						RESET);
				exit(1);
			}
			break;
		case 7:	   // R1 G1 B1 - R2 G2 B2
			exit(0);
			break;
		default:
			fprintf(stderr, "\t\033[31;1mWrong Number of Arguments%s\n", RESET);
			exit(1);
	}
}

int main(int argc, const char** argv)
{
	signal(SIGINT, signal_int);
	signal(SIGTERM, signal_int);
	signal(SIGWINCH, signal_resize);

	color_t initial_color;
	color_t ending_color;
	setColors(argc, argv, &initial_color, &ending_color);

	rgb2hsv(&initial_color);
	rgb2hsv(&ending_color);
	printf("\033[?25l");
	cls();

	getTermSize(&t_width, &t_height);

	grad_buffer = malloc(t_width * t_height);

	display_inputs(0);
	while(1)
	{
		printf("\033[H");
		gradient(t_width, t_height, &initial_color, &ending_color);
		// 60 FPS
		usleep(16666U);
	}

	free(grad_buffer);

	display_inputs(1);
	printf("\033[?25h");
	printf("\033[38;2m;\033[48;2m\n");
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

