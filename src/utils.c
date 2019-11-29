double map(double val, double dmin, double dmax, double rmin, double rmax)
{
	// sin(x) -> [3, 7]
	// [-1, 1] -> [0, 2]
	// [0, 2] * (7-3)/2 -> [0, 4]
	// [0, 4] + rmin
	return ((val - dmin) * (rmax - rmin) / (dmax - dmin)) + rmin;
}
