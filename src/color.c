// TODO Add HSV to RGB and vice versa
// TODO Add A Linear Interpolation for the color_t thing to be used in gradient

#include "utils.c"

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
	float r, g, b;
	float h, s, v;	  // 360° H, 100° for S and V
	char str[24];
} color_t;

void sgetRGB(char* buff, uint8_t r, uint8_t g, uint8_t b)
{
	sprintf(buff, "\033[48;2;%u;%u;%um", r, g, b);
}

void sgetGREY(char* buff, uint8_t g) { sprintf(buff, "\033[48;2;%u;%u;%um", g, g, g); }

const char* setGREY(color_t* color, uint8_t g)
{
	color->r = color->g = color->b = g;
	sprintf(color->str, "\033[48;2;%u;%u;%um", g, g, g);
	return color->str;
}

const char* setRGB(color_t* color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	sprintf(color->str, "\033[48;2;%u;%u;%um", r, g, b);
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
	float r = color->r / 255.;
	float g = color->g / 255.;
	float b = color->b / 255.;
	float CMax = MAX(MAX(r, g), b);
	float CMin = MIN(MIN(r, g), b);
	float delta = CMax - CMin;

	float h = 0., s = 0., v = 0.;

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

	color->h = h;
	color->s = s;
	color->v = v;
}

void hsv2rgb(color_t* color)
{
	float H = fmod((color->h / 60.), 6), S = (color->s / 100.), V = (color->v / 100.);
	float C = S * V;
	float X = C * (1. - fabs(fmod(H, 2) - 1));
	float M = V - C;

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

	color->r += M * 255.f;
	color->g += M * 255.f;
	color->b += M * 255.f;
}

const char* setStr(color_t* color)
{
	sprintf(color->str,
			"\033[48;2;%u;%u;%um",
			(uint8_t)color->r,
			(uint8_t)color->g,
			(uint8_t)color->b);
	return color->str;
}

// Maybe add a color_t* dest version of these

color_t rgbInterp(color_t first, color_t second, int curr, int total)
{
	color_t result;
	result.r = interpf(first.r, second.r, curr, total);
	result.g = interpf(first.g, second.g, curr, total);
	result.b = interpf(first.b, second.b, curr, total);
	return result;
}

color_t hsvInterp(color_t first, color_t second, int curr, int total)
{
	color_t result;
	result.h = interpf(first.h, second.h, curr, total);
	result.s = interpf(first.s, second.s, curr, total);
	result.v = interpf(first.v, second.v, curr, total);
	hsv2rgb(&result);
	return result;
}

static const char RESET[] = "\033[38m\033[48m", BLACK[] = "\033[48;2;0;0;0m",
				  WHITE[] = "\033[48;2;255;255;255m", RED[] = "\033[48;2;255;0;0m",
				  GREEN[] = "\033[48;2;0;255;0m", BLUE[] = "\033[48;2;0;0;255m",
				  YELLOW[] = "\033[48;2;255;255;0m", MAGENTA[] = "\033[48;2;255;0;255m",
				  CYAN[] = "\033[48;0;2;255;255m", PURPLE[] = "\033[48;2;127;32;183m",
				  LIME[] = "\033[48;2;111;255;8m", BROWN[] = "\033[48;2;142;69;23m",
				  ORANGE[] = "\033[48;2;255;127;8m";

#endif
