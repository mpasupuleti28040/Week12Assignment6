
#include <iostream>
#include <vector>
#include <thread>

// Function for each thread to perform part of the DAXPY operation
void daxpy_thread(double a, const std::vector<double>& x, std::vector<double>& y, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    const size_t N = 1000000; // Size of the vectors
    const size_t num_threads = 4; // Number of threads
    double a = 2.5; // Scalar multiplier

    // Initialize input vectors
    std::vector<double> x(N, 1.0); // Vector x initialized to 1.0
    std::vector<double> y(N, 2.0); // Vector y initialized to 2.0

    // Thread management
    std::vector<std::thread> threads;
    size_t chunk_size = N / num_threads;

    // Create threads and assign them portions of the vectors
    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? N : start + chunk_size;
        threads.emplace_back(daxpy_thread, a, std::cref(x), std::ref(y), start, end);
    }

    // Wait for all threads to finish
    for (auto& th : threads) {
        th.join();
    }

    // Print a message indicating completion
    std::cout << "DAXPY computation complete!" << std::endl;

    return 0;
}
