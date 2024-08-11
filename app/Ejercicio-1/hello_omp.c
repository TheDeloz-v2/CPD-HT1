#include <iostream>
#include <omp.h>

int main(int argc, char* argv[]) {
    int num_threads = 10;
    if (argc > 1) {
        num_threads = std::stoi(argv[1]);
    }

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        std::cout << "Hello from thread " << thread_id << " of " << total_threads << "!" << std::endl;
    }

    return 0;
}

