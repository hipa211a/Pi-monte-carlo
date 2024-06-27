# Pi-monte-carlo

## Some basic Information
- Use Monte Carlo to calculate value of Pi. This repo contains serial as well as parallel versions of C++ code.
- All the source files are in the `src` directory.
- Serial version, C++ thread version, OpenMP parallel version, MPI parallel version, Hybrid OpenMP+MPI parallel version and CUDA parallel version are present in this repo.
- Attempt has been made to use as much C++ code as possible, for example using containers and algorithms.
- The highest C++ standard used is C++20. In all parallel files it couldn't be used as there was a problem with compiler not recognizing some C++20 functions. Maybe in future it would be possible.
- AI models ChatGPT and ClaudeAI helped to make this code much better.
- Feel free to try it out.

## How to run it?
- Make sure you have all the compilers available. Edit them in the `Makefile`. Compilers >= `gcc-11` would be good.
- To compile all the source files
  ```
  make all
  ```
- To build specific target like omp-pi or serial-pi or cuda-pi
  ```
  make omp-pi
  make serial-pi
  make cuda-pi
  ```
- To clean all the files
  ```
  make clean
  ```
