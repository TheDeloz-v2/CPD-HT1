#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double n = 10e6;

// Funciones 
double f1(double x) {
    return x * x; // x^2
}

double f2(double x) {
    return 2 * pow(x, 3); // 2x^3
}

double f3(double x) {
    return sin(x); // sin(x)
}

double trapezoides(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        sum += f(xi);
    }

    sum += (f(a) + f(b)) / 2.0;

    return sum * h;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s (a) (b)\n", argv[0]);
        return 1;
    }

    const double a = atof(argv[1]);
    const double b = atof(argv[2]);

    double result = trapezoides(f3, a, b, n);

    printf("Con n = %e\n", n);
    printf("En el intervalo [%f, %f]\n", a, b);
    printf("La aproximacion es = %f\n", result);

    return 0;
}
