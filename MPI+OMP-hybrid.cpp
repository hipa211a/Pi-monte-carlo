#include <iostream>
#include <random>
#include <cmath>
#include <mpi.h>
#include <omp.h>

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

    long long int niter = 100000000; // Total number of iterations
    int local_niter = niter / size; // Iterations per process
    int local_rank_count = 0; //local count for a single process
    int global_count = 0;   //global count

    omp_set_num_threads(4);
    
    if (rank == 0){
        std::cout << "Total MPI ranks are " << size << std::endl;
    }
    
    #pragma omp parallel
    {
        for(int i=0; i < size ; i++)
        {
            if (rank == i)
            {
                #pragma omp single
                {
                    std::cout << "I am rank " << rank << std::endl;
                    std::cout << "Number of OMP threads per rank= " << omp_get_num_threads() << std::endl;
                }
            }
        }
        
        int local_thread_count = 0;

        // Create a random number generator for each thread
        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd() + rank + omp_get_thread_num()); // Use rank and thread id to ensure different seeds

        #pragma omp for nowait
        for (int i = 0; i < local_niter; ++i) {
            double x = random_double(-1.0, 1.0, gen);
            double y = random_double(-1.0, 1.0, gen);
            double z = std::sqrt(x*x + y*y);
            if (z <= 1) {
                ++local_thread_count;
            }
        }

        #pragma omp atomic
        local_rank_count += local_thread_count;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    
    // Sum up all local counts
    MPI_Reduce(&local_rank_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate and print Pi on the root process
    if (rank == 0) {
        double Pi = 4.0 * global_count / static_cast<double>(niter);
        std::cout << "Pi = " << Pi << std::endl;
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}