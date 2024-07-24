#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>

const int c = 3e8;//скорость в  м/С

struct data {
    double m, v, e;//масса в кг, скорость в м/с
}
test_data[] = {
    {1.6726e-27, 1, 938}, //протон, тут должен выдать ошибку, должно быть 938 000 000 или что-то по порядку
    {5, 10, 250}, // должно пройти без ошибок
    {1, 4e8, 1000} //тут должна быть ошибка по скорости света 
};

double calc_newton(double m, double v)  {
    if (m < 0.0000001 && m==0 || v > c) {
        return nan(""); 
    }

    double energy = m * v * v / 2;
    return energy;

}

double calc_newton_ovr(struct data *input) {return calc_newton(input->m, input->v);}

double calc_einstein(double m, double v) {
    
    if (m >= 0.0000001 && m==0 || v > c) {
        return nan("");
    }

    double energy = m * c * c / 1.6 / 1e-19;//ради приличия сделаю перевод в эвы
    return energy;
}

double calc_einstein_ovr(struct data *input) {return calc_einstein(input->m, input->v);} 

int verify_calc(double m, double v, double e, double *actual) {
    if (m < 0.0000001 && m!=0) {
        *actual = calc_einstein(m, v);
    }
    else if (m >= 0.0000001 && m!=0) {
        *actual = calc_newton(m, v);
    }

    if (*actual != e) { 
        return 0;
    }

    else {
        return 1;
    }
    //return *actual == e;
}

int main() {

    struct data *test = test_data;
    double actual;
    int nerrs = 0;

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {
		if (!verify_calc(test->m, test->v, test->e, &actual)) {
			nerrs++;
			printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->e, actual);
		}
	}
	return nerrs;
}

