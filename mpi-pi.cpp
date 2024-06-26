#include <iostream>
#include <random>
#include <cmath>
#include <mpi.h>

// Function to generate random numbers between m and n
double random_double(double m, double n, std::mt19937& gen)
{
    std::uniform_real_distribution<> dis(m, n);
    return dis(gen);
}

int main(int argc, char** argv) 
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int niter = 1000000; // Total number of iterations
    int local_niter = niter / size; // Iterations per process
    int local_count = 0;
    int global_count = 0;

    // Create a random number generator for each process
    std::random_device rd;
    std::mt19937 gen(rd() + rank); // Use rank to ensure different seeds

    // Perform local Monte Carlo simulations
    for (int i = 0; i < local_niter; ++i) {
        double x = random_double(-1.0, 1.0, gen);
        double y = random_double(-1.0, 1.0, gen);
        if (x*x + y*y <= 1.0f) {
            ++local_count;
        }
    }

    // Sum up all local counts
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate and print Pi on the root process
    if (rank == 0) {
        double Pi = 4.0 * global_count / static_cast<double>(niter);
        std::cout << "Pi = " << Pi << std::endl;
    }

    MPI_Finalize();
    return 0;
}