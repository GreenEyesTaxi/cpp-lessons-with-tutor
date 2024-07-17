#include <stdio.h>
#include <string.h>
#include <time.h>

struct data {
	double a, b, c;
	double k;
	double w, x, y, z;
};

double f_copy(struct data input) {
	double res;
	res =  input.a;
	res += input.b;
	res += input.c;
	res *= input.k;
	res -= input.w;
	res -= input.x;
	res -= input.y;
	res -= input.z;
	return res;
}

double f_ptr(struct data *input) {
	double res;
	res =  input->a;
	res += input->b;
	res += input->c;
	res *= input->k;
	res -= input->w;
	res -= input->x;
	res -= input->y;
	res -= input->z;
	return res;
}

double f_sep(double a, double b, double c, double k, double w, double x, double y, double z) {
	double res;
	res =  a;
	res += b;
	res += c;
	res *= k;
	res -= w;
	res -= x;
	res -= y;
	res -= z;
	return res;
}

int
main(int argc, char **argv) {
	time_t start, end;
	struct data d;
	unsigned long long nops, step = 10000;

	// TODO

	return 0;
}
