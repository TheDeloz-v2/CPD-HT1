#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

const double n = 1e6;
double *local_sums;  // Arreglo global para almacenar las sumas locales de cada thread

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

double trapezoides(double (*f)(double), double a, double b, int n, int num_threads) {
    double h = (b - a) / n; // Ancho de cada trapezoide
    double sum = 0.0;

    // Reservar memoria para el arreglo global
    local_sums = (double *)malloc(num_threads * sizeof(double));

    // Inicializar las sumas locales a cero
    for (int i = 0; i < num_threads; i++) {
        local_sums[i] = 0.0;
    }

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int n_local = n / num_threads;
        double a_local = a + thread_id * n_local * h;
        double b_local = a_local + n_local * h;
        double local_sum = 0.0;

        for (int i = 1; i < n_local; i++) {
            double xi = a_local + i * h;
            local_sum += f(xi);
        }

        printf("Thread %d: [%f, %f]\n", thread_id, a_local, b_local);

        local_sum += (f(a_local) + f(b_local)) / 2.0;

        local_sums[thread_id] = local_sum * h;
    }

    for (int i = 0; i < num_threads; i++) {
        sum += local_sums[i];
    }

    free(local_sums);

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s a b <cantidad de threads>\n", argv[0]);
        return 1;
    }

    const double a = atof(argv[1]);
    const double b = atof(argv[2]);
    const int num_threads = atoi(argv[3]);
    int n = 1000000; // n = 10^6

    double result = trapezoides(f3, a, b, n, num_threads);

    printf("Con n = %d y %d threads\n", n, num_threads);
    printf("En el intervalo [%f, %f]\n", a, b);
    printf("La aproximacion es %f\n", result);

    return 0;
}

