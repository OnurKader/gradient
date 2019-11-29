#include "color.h"

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
	return 0;
}
