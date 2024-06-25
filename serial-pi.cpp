#include <iostream>
#include <random>
#include <ranges>

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
    int niter = 1e5;

    //Use a lambda expression combined with count_if function to count number of points inside a unit circle
    auto count = std::count_if(std::views::iota(1, niter + 1).begin(), std::views::iota(1, niter + 1).end(),[](auto) {
        double x = random_double(-1.0, 1.0);
        double y = random_double(-1.0, 1.0);
        double z = std::sqrt(x*x + y*y);
        return z <= 1;
    });

    //Calculate value of Pi
    auto Pi = 4*(count/static_cast<double>(niter));
    
    //Print the value
    std::cout << "Pi = " << Pi << std::endl;
    
    return EXIT_SUCCESS;
}
