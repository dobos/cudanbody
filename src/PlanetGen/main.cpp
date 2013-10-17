#include <time.h>
#include <math.h>
#include <cstdlib>
#include <iostream>

#define PI 3.1415926535897932384626
#define K2 0.0002959122082855911025

#define MASS_STAR 1				// M_sol
#define RAD_STAR 0.005			// AU

#define MASS_SUN 1.9891E+30
#define MASS_FACTOR 5e-7		// M_sol
#define MASS_MU log(4.0)
#define MASS_S 0.3
#define MASS_MIN 1
#define MASS_MAX 10

#define DIST_MIN 1				// AU
#define DIST_MAX 10				// AU

#define DENSITY	3000.0			// kg m-3
#define AU 149.6e9				// m

typedef double var_t;

using namespace std;

// Draw a number from a given distribution
var_t generate_random(var_t xmin, var_t xmax, var_t p(var_t))
{
	var_t x;
	var_t y;

	do
	{
		x = xmin + (var_t)rand() / RAND_MAX * (xmax - xmin);
		y = (var_t)rand() / RAND_MAX;
	}
	while (y > p(x));

	return x;
}

var_t pdf_mass_lognormal(var_t x)
{
	return 1.0 / sqrt(2 * PI) / MASS_S * exp(-pow(log(x) - MASS_MU, 2) / 2 / MASS_S / MASS_MU);
}

var_t pdf_distance_squared(var_t d)
{
	return d * d / DIST_MAX / DIST_MAX;
}

var_t pdf_distance_exp(var_t d)
{
	return exp(-d) * d * d;
}

var_t pdf_const(var_t x)
{
	return 1;
}

void calculate_circle_coord(var_t d, var_t phi, var_t* x, var_t* y)
{
	*x = d * cos(phi);
	*y = d * sin(phi);
}

void calculate_circle_veloc(var_t d, var_t phi, var_t* vx, var_t* vy)
{
	var_t v = sqrt(K2 * MASS_STAR / d);
	
	*vx = v * sin(phi);
	*vy = - v * cos(phi);
}

var_t calculate_radius(var_t m)
{
	var_t V = m * MASS_SUN / DENSITY;	// m3
	V /= AU * AU * AU;		// AU3
	
	return pow(3.0 / 4.0 / PI * V, 1.0 / 3.0);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int n = atoi(argv[1]);

	var_t d;
	var_t phi;
	var_t m;

	var_t x, y, z;
	var_t vx, vy, vz;
	var_t r;

	char sep = ' ';

	// Output central mass
	cout << 0.0 << sep;
	cout << 0.0 << sep;
	cout << MASS_STAR << sep << RAD_STAR << sep;
	cout << 0.0 << sep << 0.0 << sep << 0.0 << sep;
	cout << 0.0 << sep << 0.0 << sep << 0.0;
	cout << endl;

	// Output planets
	for (int i = 1; i < n; i ++)
	{
		d = generate_random(DIST_MIN, DIST_MAX, pdf_distance_squared);
		phi = generate_random(0, 2*PI, pdf_const);
		m = MASS_FACTOR * generate_random(MASS_MIN, MASS_MAX, pdf_mass_lognormal);

		calculate_circle_coord(d, phi, &x, &y);
		calculate_circle_veloc(d, phi, &vx, &vy);
		r = calculate_radius(m);
		z = vz = 0;

		cout << i << sep;
		cout << 0 << sep;
		cout << m << sep << r << sep;
		cout << x << sep << y << sep << z << sep;
		cout << vx << sep << vy << sep << vz;
		cout << endl;
	}

	return 0;
}