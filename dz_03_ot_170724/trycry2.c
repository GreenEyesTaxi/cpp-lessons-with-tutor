#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>

const double c = 3e8;//скорость в  м/С
double error_rate = 0.005;

struct data {
    double m, v, en, ee;//масса в кг, скорость в м/с
}
test_data[] = {
    {1.6726e-27, 1, 938}, //протон, тут должен выдать ошибку, должно быть 938 000 000 или что-то по порядку
    {5, 10, 250, 4.5e17}, // должно пройти без ошибок
    {1, 4e8, 1000, NAN} //тут должна быть ошибка по скорости света 
};

double calc_newton(double m, double v)  {
    double en = m * v * v / 2;
    return en;

}

double calc_einstein(double m, double v) {
    if (v >  c) {
        return nan("");
    }

    double ee = m * c * c;
    return ee;
}

int verify_calc(double m, double v, double expected, double *actual, double (*calc)(double m, double v)) {
    *actual = calc(m,v);
    double error_actual = fmod(*actual, expected);

    if (isnan(expected)) {
        return NAN;
    }
    
    else {
        if (*actual != expected) { 
            return 0;
        }

        else if ( error_actual <= error_rate){
            return 1;
        }
        
    }
}    

int main() {

    struct data *test = test_data;
    double actual;
    int nerrs = 0;
    struct data real;

    for (size_t i = 0; i < sizeof(test_data)/sizeof(test_data[0]); i++, test++) {
        if (!verify_calc(test->m, test->v, test->en, &actual, calc_newton)) {
			nerrs++;
			printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->en, actual);
		}
        if (!verify_calc(test->m, test->v, test->ee, &actual, calc_einstein)) {
            nerrs++;
            printf("test failed for %f and %f: expected %f but got %f\n",
			    test->m, test->v, test->ee, actual);
        }
    }

    if (nerrs != 0) {
        return 2;
    }
    else {
        printf("Enter mass and speed:\t");
        scanf("%lf%lf", &real.m, &real.v);

        real.en = calc_newton(real.m, real.v);
        real.ee = calc_einstein(real.m, real.v);

        if (isnan(real.en) || isnan(real.ee)) {
            return 1;
        }
        else {
            printf("Newton energy = %lf, Einstein energy = %lf\n", real.en, real.ee);
            return 0;
        }
    }

}

