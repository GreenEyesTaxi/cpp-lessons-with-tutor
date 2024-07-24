#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>

const double c = 3e8;//скорость в  м/С

struct data {
    double m, v, en, ee;//масса в кг, скорость в м/с
}
test_data[] = {
    //{1.6726e-27, 1, 938}, //протон, тут должен выдать ошибку, должно быть 938 000 000 или что-то по порядку
    {5, 10, 250, 4.5e17}, // должно пройти без ошибок
    {1, 4e8, 1000, 2000} //тут должна быть ошибка по скорости света 
};

double calc_newton(double m, double v, double en)  {
    /*if (m < 0.0000001 && m >= 0 || v > c) {
        return nan(""); 
    }*/

    en = m * v * v / 2;
    return en;

}

double calc_newton_ovr(struct data *input) {return calc_newton(input->m, input->v, input->en);}

double calc_einstein(double m, double v, double ee) {
    
    /*if (m >= 0.0000001 && m==0 || v > c) {
        return nan("");
    }*/

    ee = m * c * c / 1.6 / 1e-19;//ради приличия сделаю перевод в эвы
    return ee;
}

double calc_einstein_ovr(struct data *input) {return calc_einstein(input->m, input->v, input->ee);} 

int verify_calc(struct data *d, double *actual, double (*calc)(struct data *)) {
    return *actual == calc(d);
}

int main() {

    struct data *test = test_data;
    double actual;
    int nerrs = 0;

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {
        if (!verify_calc(test, &actual, calc_newton_ovr)) {
			nerrs++;
			printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->en, actual);
		}
    }

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {    
        if (!verify_calc(test, &actual, calc_einstein_ovr)) {
            nerrs++;
            printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->ee, actual);
        }
	}
	return nerrs;
}

