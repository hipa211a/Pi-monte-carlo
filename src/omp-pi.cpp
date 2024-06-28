#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <chrono>
#include <omp.h>

//Function to generate random numbers between m and n
//Returns a single value of type double
double random_double(double m, double n)
{
    static thread_local std::random_device rd; //seed for the random number engine
    static thread_local std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(m, n); // Generate random numbers between -1 and 1
    return dis(gen);
}

int main() {
    int niter = 1000000; 
    int count = 0;
    omp_set_num_threads(4);
    
    //Start time measurement
    const auto tstart{std::chrono::high_resolution_clock::now()};

    #pragma omp parallel
    {
        #pragma omp single
        {
            std::cout << "Number of OMP threads = " << omp_get_num_threads() << std::endl;
        }
        
        int local_count = 0;

        #pragma omp for nowait
        for (int i = 0; i < niter; ++i) {
            double x = random_double(-1.0, 1.0);
            double y = random_double(-1.0, 1.0);
            if (x*x + y*y <= 1.0f) {
                ++local_count;
            }
        }

        #pragma omp atomic
        count += local_count;
    }

    //End the time measurement
    const auto tend{std::chrono::high_resolution_clock::now()};

    //Calculate value of Pi
    auto Pi = 4.0 * (count/static_cast<double>(niter));
    
    //Print the value
    std::cout << "Pi = " << Pi << std::endl;
    std::cout << "M_PI: " << M_PI << std::endl;
    std::cout << "Difference from M_PI: " << std::abs(Pi - M_PI) << std::endl;
    
    //Duration
    auto tduration = std::chrono::duration_cast<std::chrono::milliseconds>(tend-tstart).count();
    std::cout << "Time taken = " << tduration << "ms" << std::endl;

    return 0;
}