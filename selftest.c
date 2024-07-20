#include <stdio.h>
#include <string.h>
#include <float.h>

double sum(double x, double y) {
	return x + y;
}

int verify_sum(double x, double y, double expected, double *got) {
	*got = sum(x, y);
	return *got == expected;
}

struct test_item {
	double x, y, result;
} test_data[] = {
	{  1,  1,  2 },
	{ -1,  1,  0 },
	{ -1, -1, -2 },
	{  0,  0,  1 }    // would fail
};

int main() {
	struct test_item *item = test_data;
	double actual;
	int nerrs = 0;

	for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, item++) {
		if (!verify_sum(item->x, item->y, item->result, &actual)) {
			nerrs++;
			printf("test failed for %f and %f: expected %f but got %f\n",
			    item->x, item->y, item->result, actual);
		}
	}
	return nerrs;
}
