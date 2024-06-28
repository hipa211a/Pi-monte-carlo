# Compilers
CXX = g++-11
MPICXX = mpic++
NVCC = nvcc

# Compiler flags
CXXFLAGS = -std=c++20 -fopenmp -pthread -O2
MPICXXFLAGS = -std=c++17 -fopenmp -O2
NVCCFLAGS = -std=c++14 -O2

# Directories
SRCDIR = src
BINDIR = bin

# Targets
PROGRAMS =  serial-pi omp-pi pi-thread mpi-pi MPI+OMP-hybrid cuda-pi
TARGETS = $(addprefix $(BINDIR)/, $(PROGRAMS))

# Default target
all: $(TARGETS)

# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Generic rules for each program
$(PROGRAMS): %: $(BINDIR)/%
	@echo "Compiled $@"

# Explicit compilation rules
$(BINDIR)/serial-pi: $(SRCDIR)/serial-pi.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BINDIR)/pi-thread: $(SRCDIR)/pi-thread.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BINDIR)/omp-pi: $(SRCDIR)/omp-pi.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BINDIR)/cuda-pi: $(SRCDIR)/cuda-pi.cu | $(BINDIR)
	$(NVCC) $(NVCCFLAGS) $< -o $@

$(BINDIR)/mpi-pi: $(SRCDIR)/mpi-pi.cpp | $(BINDIR)
	$(MPICXX) $(MPICXXFLAGS) $< -o $@

$(BINDIR)/MPI+OMP-hybrid: $(SRCDIR)/MPI+OMP-hybrid.cpp | $(BINDIR)
	$(MPICXX) $(MPICXXFLAGS) $< -o $@

# Clean target
clean:
	rm -rf $(BINDIR)

.PHONY: all clean $(PROGRAMS)