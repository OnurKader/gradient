// TODO Add HSV to RGB and vice versa
// TODO Add A Linear Interpolation for the color_t thing to be used in gradient

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	uint8_t r, g, b;
	char str[24];
} color_t;

void sgetRGB(char* buff, uint8_t r, uint8_t g, uint8_t b)
{
	sprintf(buff, "\033[38;2;%u;%u;%um", r, g, b);
}

void setGREY(char* buff, uint8_t g) { sprintf(buff, "\033[38;2;%u;%u;%um", g, g, g); }

const char* setGREY(color_t* color, uint8_t g)
{
	color->r = color->g = color->b = g;
	sprintf(color->str, "\033[38;2;%u;%u;%um", g, g, g);
	return color->str;
}

const char* setRGB(color_t* color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	sprintf(color->str, "\033[38;2;%u;%u;%um", r, g, b);
	return color->str;
}

const char* setStr(color_t* color)
{
	sprintf(color->str, "\033[38;2;%u;%u;%um", color->r, color->g, color->b);
	return color->str;
}

static const char RESET[] = "\033[m", BLACK[] = "\033[38;2;0;0;0m",
				  WHITE[] = "\033[38;2;255;255;255m", RED[] = "\033[38;2;255;0;0m",
				  GREEN[] = "\033[38;2;0;255;0m", BLUE[] = "\033[38;2;0;0;255m",
				  YELLOW[] = "\033[38;2;255;255;0m", MAGENTA[] = "\033[38;2;255;0;255m",
				  CYAN[] = "\033[38;0;2;255;255m", PURPLE[] = "\033[38;2;127;32;183m",
				  LIME[] = "\033[38;2;111;255;8m", BROWN[] = "\033[38;2;142;69;23m",
				  ORANGE[] = "\033[38;2;255;127;8m";
#endif
