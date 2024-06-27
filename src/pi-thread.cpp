#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>

std::atomic<unsigned long long> points_inside_circle(0);
std::atomic<unsigned long long> total_points(0);

void monte_carlo_pi(unsigned long long points_per_thread) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    unsigned long long local_points_inside = 0;

    for (unsigned long long i = 0; i < points_per_thread; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x*x + y*y <= 1.0) {
            local_points_inside++;
        }
    }

    points_inside_circle += local_points_inside;
    total_points += points_per_thread;
}

int main() {
    unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Num threads: " << num_threads << std::endl;
    unsigned long long points_per_thread = 1'000'000;

    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(monte_carlo_pi, points_per_thread);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    double pi_estimate = 4.0 * static_cast<double>(points_inside_circle) / static_cast<double>(total_points);

    std::cout << "Estimated Pi: " << pi_estimate << std::endl;
    std::cout << "M_PI: " << M_PI << std::endl;
    std::cout << "Difference from M_PI: " << std::abs(pi_estimate - M_PI) << std::endl;

    return EXIT_SUCCESS;
}