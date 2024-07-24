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

double calc_newton(double m, double v)  {
    /*if (m < 0.0000001 && m >= 0 || v > c) {
        return nan(""); 
    }*/

    double en = m * v * v / 2;
    return en;

}

//double calc_newton_ovr(struct data *input) {return calc_newton(input->m, input->v);}

double calc_einstein(double m, double v) {
    
    /*if (m >= 0.0000001 && m==0 || v > c) {
        return nan("");
    }*/

    double ee = m * c * c;//ради приличия сделаю перевод в эвы
    return ee;
}

//double calc_einstein_ovr(struct data *input) {return calc_einstein(input->m, input->v);} 

int verify_calc(double m, double v, double expected, double *actual, double (*calc)(double m, double v)) {
    *actual = calc(m,v);
    return *actual == expected;
}

int main() {

    struct data *test = test_data;
    double actual;
    int nerrs = 0;

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {
        if (!verify_calc(test->m, test->v, test->en, &actual, calc_newton)) {
			nerrs++;
			printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->en, actual);
		}
    }

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {    
        if (!verify_calc(test->m, test->v, test->en, &actual, calc_einstein)) {
            nerrs++;
            printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->ee, actual);
        }
	}
	return nerrs;
}

