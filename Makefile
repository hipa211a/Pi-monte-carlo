# Compiler
CXX = g++-11
MPICXX = mpic++

# Compiler flags
CXXFLAGS = -std=c++20 -fopenmp -O2
MPICXXFLAGS = -std=c++17 -fopenmp -O2

# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)

#Rules 
default: serial-pi omp-pi mpi-pi MPI+OMP-hybrid

serial-pi: serial-pi.cpp
	$(CXX) $(CXXFLAGS) -o serial-pi serial-pi.cpp

omp-pi: omp-pi.cpp
	$(CXX) $(CXXFLAGS) -o omp-pi omp-pi.cpp

pi-thread: pi-thread.cpp
	$(CXX) $(CXXFLAGS) -o pi-thread pi-thread.cpp

mpi-pi: mpi-pi.cpp
	$(MPICXX) $(MPICXXFLAGS) -o mpi-pi mpi-pi.cpp

MPI+OMP-hybrid: MPI+OMP-hybrid.cpp
	$(MPICXX) $(MPICXXFLAGS) -o MPI+OMP-hybrid MPI+OMP-hybrid.cpp

clean:
	@$(RM) $(BIN)

# Phony targets
.PHONY: default clean