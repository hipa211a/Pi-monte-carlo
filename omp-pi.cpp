#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
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
            double z = std::sqrt(x*x + y*y);
            if (z <= 1) {
                ++local_count;
            }
        }

        #pragma omp atomic
        count += local_count;
    }

    //Calculate value of Pi
    auto Pi = 4*(count/static_cast<double>(niter));
    
    //Print the value
    std::cout << "Pi = " << Pi << std::endl;

    return 0;
}