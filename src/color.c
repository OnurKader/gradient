// TODO Add HSV to RGB and vice versa
// TODO Add A Linear Interpolation for the color_t thing to be used in gradient

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef COLOR_H
#	define COLOR_H

#	define MAX(a, b) ((a) < (b) ? (b) : (a))
#	define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct
{
	uint8_t r, g, b;
	uint16_t h;
	uint8_t s, v;	 // 360° H, 100° for S and V
	char str[24];
} color_t;

void sgetRGB(char* buff, uint8_t r, uint8_t g, uint8_t b)
{
	sprintf(buff, "\033[38;2;%u;%u;%um", r, g, b);
}

void sgetGREY(char* buff, uint8_t g) { sprintf(buff, "\033[38;2;%u;%u;%um", g, g, g); }

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

void setHSV(color_t* color, uint16_t h, uint8_t s, uint8_t v)
{
	color->h = h;
	color->s = s;
	color->v = v;
	// TODO add sprintf and a hsv2rgb convo here
	// TODO sgetHSV too
}

void rgb2hsv(color_t* color)
{
	double r = color->r / 255.;
	double g = color->g / 255.;
	double b = color->b / 255.;
	double CMax = MAX(MAX(r, g), b);
	double CMin = MIN(MIN(r, g), b);
	double delta = CMax - CMin;

	double h, s, v;

	if(delta > 0.)
	{
		if(CMax == r)
			h = 60. * (fmod((g - b) / delta, 6));
		else if(CMax == g)
			h = 60. * ((b - r) / delta + 2);
		else if(CMax == b)
			h = 60. * ((r - g) / delta + 4);

		if(CMax > 0)
			s = delta / CMax;
		else
			s = 0.;
		v = CMax;
	}
	else
	{
		h = s = 0.;
		v = CMax;
	}

	if(h < 0)
		h += 360.;
	s *= 100.;
	v *= 100.;

	color->h = (uint16_t)h;
	color->s = (uint8_t)s;
	color->v = (uint8_t)v;
}

void hsv2rgb(color_t* color)
{
	double H = fmod((color->h / 60.), 6), S = (color->s / 100.), V = (color->v / 100.);
	double C = S * V;
	double X = C * (1. - fabs(fmod(H, 2) - 1));
	double M = V - C;

	if(0 <= H && H < 1)
	{
		color->r = C * 255;
		color->g = X * 255;
		color->b = 0;
	}
	else if(1 <= H && H < 2)
	{
		color->r = X * 255;
		color->g = C * 255;
		color->b = 0;
	}
	else if(2 <= H && H < 3)
	{
		color->r = 0;
		color->g = C * 255;
		color->b = X * 255;
	}
	else if(3 <= H && H < 4)
	{
		color->r = 0;
		color->g = X * 255;
		color->b = C * 255;
	}
	else if(4 <= H && H < 5)
	{
		color->r = X * 255;
		color->g = 0;
		color->b = C * 255;
	}
	else if(5 <= H && H < 6)
	{
		color->r = C * 255;
		color->g = 0;
		color->b = X * 255;
	}
	else
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}

	color->r += M * 255;
	color->g += M * 255;
	color->b += M * 255;
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
