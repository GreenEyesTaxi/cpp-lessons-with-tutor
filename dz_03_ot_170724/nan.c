#include <math.h>
#include <stdio.h>

int x;

int add_to_x(int y) { return x + y; }

int main() {
	double a, b, c;
	int n;
	a = NAN;
	b = 123;
	c = a + b;
	printf("a+b=%f\n", c);
	n = a <= b;
	printf("a<=b=%d\n", n);
	n = b <= a;
	printf("b<=a=%d\n", n);
	return 0;
}

