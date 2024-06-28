#include <iostream>
#include <random>
#include <ranges>
#include <chrono>

//Function to generate random numbers between m and n
//Returns a single value of type double
auto random_double(double m, double n)
{
    std::random_device rd; //seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(m, n); // Generate random numbers between -1 and 1
    return dis(gen);
}

int main()
{
    int niter = 1e6;

    //Start time measurement
    const auto tstart{std::chrono::high_resolution_clock::now()};

    //Use a lambda expression combined with count_if function to count number of points inside a unit circle
    auto count = std::count_if(std::views::iota(1, niter + 1).begin(), std::views::iota(1, niter + 1).end(),[](auto) {
        double x = random_double(-1.0, 1.0);
        double y = random_double(-1.0, 1.0);
        return x*x + y*y <= 1;
    });
    
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
    
    return EXIT_SUCCESS;
}
