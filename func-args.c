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
double f_copy_ovr(struct data *input) { return f_copy(*input); }

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
double f_ptr_ovr(struct data *input) { return f_ptr(input); }

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
double f_sep_ovr(struct data *input) { return f_sep(input->a, input->b, input->c, input->k, input->w, input->x, input->y, input->z); }

void measure(struct data *d, double (*pf)(struct data *)) {
	time_t start, end;
	unsigned long long nops;

	start = time(NULL);
	time(&start);
	for (nops = 0; nops < 100000000; nops++) {
		pf(d);
	}
	end = time(NULL);
	printf("it took %llu seconds\n", (unsigned long long)(end - start));
}

int
main(int argc, char **argv) {
	struct data d;

	measure(&d, f_copy_ovr);
	measure(&d, f_ptr_ovr);
	measure(&d, f_sep_ovr);

	return 0;
}
