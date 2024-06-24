#include <iostream>
#include <random>

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
    double x,y,z,Pi;
    double niter = 1e4;
    int count=0;
    for(int i=0; i < niter; ++i)
    {
        x = random_double(-1.0,1.0);
        y = random_double(-1.0,1.0);
        z = std::sqrt(x*x+y*y);
        if(z <= 1)
        {
            ++count;
        }
    }
    Pi = 4*(count/niter);
    std::cout << "Pi = " << Pi << std::endl;
    return EXIT_SUCCESS;
}
