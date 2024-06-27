#include <iostream>
#include <cmath>
#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <memory>

constexpr int BLOCKS = 256;
constexpr int THREADS_PER_BLOCK = 256;

__global__ void monte_carlo_pi(unsigned long long* count, unsigned long long iterations, curandState* states) {
    unsigned int tid = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned long long local_count = 0;
    curandState localState = states[tid];

    for (unsigned long long i = 0; i < iterations; i++) {
        float x = curand_uniform(&localState);
        float y = curand_uniform(&localState);
        if (x*x + y*y <= 1.0f) {
            local_count++;
        }
    }

    atomicAdd(count, local_count);
}

__global__ void setup_random_states(curandState* states) {
    unsigned int tid = threadIdx.x + blockIdx.x * blockDim.x;
    curand_init(clock64(), tid, 0, &states[tid]);
}

struct CudaDeleter {
    void operator()(void* ptr) const {
        cudaFree(ptr);
    }
};

template<typename T>
using CudaUniquePtr = std::unique_ptr<T, CudaDeleter>;

template<typename T>
CudaUniquePtr<T> make_cuda_unique(size_t size) {
    T* ptr;
    cudaMalloc(&ptr, size);
    return CudaUniquePtr<T>(ptr);
}

int main() {
    unsigned long long h_count = 0;
    constexpr unsigned long long iterations = 1000000;

    auto d_count = make_cuda_unique<unsigned long long>(sizeof(unsigned long long));
    auto d_states = make_cuda_unique<curandState>(BLOCKS * THREADS_PER_BLOCK * sizeof(curandState));

    cudaMemcpy(d_count.get(), &h_count, sizeof(unsigned long long), cudaMemcpyHostToDevice);

    setup_random_states<<<BLOCKS, THREADS_PER_BLOCK>>>(d_states.get());

    monte_carlo_pi<<<BLOCKS, THREADS_PER_BLOCK>>>(d_count.get(), iterations, d_states.get());

    cudaMemcpy(&h_count, d_count.get(), sizeof(unsigned long long), cudaMemcpyDeviceToHost);

    double pi_estimate = 4.0 * static_cast<double>(h_count) / static_cast<double>(iterations * BLOCKS * THREADS_PER_BLOCK);

    std::cout << "Estimated Pi: " << pi_estimate << std::endl;
    std::cout << "Difference from M_PI: " << std::abs(pi_estimate - M_PI) << std::endl;

    return 0;
}