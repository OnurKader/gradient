double map(double val, double dmin, double dmax, double rmin, double rmax)
{
	return ((val - dmin) * (rmax - rmin) / (dmax - dmin)) + rmin;
}

int interp(int start, int end, int curr, int total)
{
	return start + ((end - start) * curr / total);
}

double interpd(double start, double end, double curr, double total)
{
	return start + ((end - start) * curr / total);
}

float interpf(float start, float end, float curr, float total)
{
	return start + ((end - start) * curr / total);
}

