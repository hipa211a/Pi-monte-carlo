# Compiler
CXX = g++-11
MPICXX = mpic++

# Compiler flags
CXXFLAGS = -std=c++20 -fopenmp -Wall -Wextra -O2
MPICXXFLAGS = -std=c++17 -fopenmp -Wall -Wextra -O2

# Source files
SOURCES = omp-pi.cpp serial-pi.cpp mpi-pi.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executables
EXECUTABLES = omp-pi serial-pi mpi-pi

# Default target
all: $(EXECUTABLES)

# Rule for linking
mpi-pi: mpi-pi.o
	$(MPICXX) $(MPICXXFLAGS) -o $@ $<

omp-pi: omp-pi.o
	$(CXX) $(CXXFLAGS) -o $@ $<

serial-pi: serial-pi.o
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule for compiling
mpi-pi.o: mpi-pi.cpp
	$(MPICXX) $(MPICXXFLAGS) -c $<

omp-pi.o: omp-pi.cpp
	$(CXX) $(CXXFLAGS) -c $<

serial-pi.o: serial-pi.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

# Phony targets
.PHONY: all clean