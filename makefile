# Compiler
CXX = g++-11

# Compiler flags
CXXFLAGS = -std=c++20 -fopenmp -Wall -Wextra -O2

# Source files
SOURCES = omp-pi.cpp serial-pi.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executables
EXECUTABLES = omp-pi serial-pi

# Default target
all: $(EXECUTABLES)

# Rule for linking
omp-pi: omp-pi.o
	$(CXX) $(CXXFLAGS) -o $@ $<

serial-pi: serial-pi.o
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule for compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

# Phony targets
.PHONY: all clean