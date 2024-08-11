#include <iostream>
#include <omp.h>

int main(int argc, char* argv[]) {

    // Cantidad de threads default

    int num_threads = 10;
    if (argc > 1) {
        num_threads = std::stoi(argv[1]);
    }

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        if (thread_id % 2 == 0) {
            // ID Par
            printf("Saludos del hilo %d\n", thread_id);
        } else {
            // ID Impar
            printf("Feliz cumpleaños número %d!\n", total_threads);
        }
    }

    return 0;
}
