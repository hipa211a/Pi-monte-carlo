# Compilers
CXX = g++-11
MPICXX = mpic++
NVCC = nvcc

# Compiler flags
CXXFLAGS = -std=c++20 -fopenmp -O2
MPICXXFLAGS = -std=c++17 -fopenmp -O2
NVCCFLAGS = -std=c++14 -O2

# Directories
SRCDIR = src
BINDIR = bin

# Explicit targets
TARGETS = $(BINDIR)/serial-pi $(BINDIR)/omp-pi $(BINDIR)/mpi-pi $(BINDIR)/MPI+OMP-hybrid $(BINDIR)/cuda-pi

# Default target
all: $(BINDIR) $(TARGETS)

# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/serial-pi: $(SRCDIR)/serial-pi.cpp
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/serial-pi $(SRCDIR)/serial-pi.cpp

$(BINDIR)/omp-pi: $(SRCDIR)/omp-pi.cpp
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/omp-pi $(SRCDIR)/omp-pi.cpp

$(BINDIR)/pi-thread: $(SRCDIR)/pi-thread.cpp
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/pi-thread $(SRCDIR)/pi-thread.cpp

$(BINDIR)/mpi-pi: $(SRCDIR)/mpi-pi.cpp
	$(MPICXX) $(MPICXXFLAGS) -o $(BINDIR)/mpi-pi $(SRCDIR)/mpi-pi.cpp

$(BINDIR)/MPI+OMP-hybrid: $(SRCDIR)/MPI+OMP-hybrid.cpp
	$(MPICXX) $(MPICXXFLAGS) -o $(BINDIR)/MPI+OMP-hybrid $(SRCDIR)/MPI+OMP-hybrid.cpp

$(BINDIR)/cuda-pi: $(SRCDIR)/cuda-pi.cu
	$(NVCC) $(NVCCFLAGS) -o $(BINDIR)/cuda-pi $(SRCDIR)/cuda-pi.cu

clean:
	rm -rf $(BINDIR)

# Phony targets
.PHONY: all clean