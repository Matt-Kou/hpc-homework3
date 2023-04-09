CXX = g++
CXXFLAGS = -fopenmp -std=c++11 -O3 -march=native

all: gs2D-omp jacobi2D-omp omp-scan

gs2D-omp: gs2D-omp.cpp
	$(CXX) $(CXXFLAGS) gs2D-omp.cpp -o gs2D-omp

jacobi2D-omp: jacobi2D-omp.cpp
	$(CXX) $(CXXFLAGS) jacobi2D-omp.cpp -o jacobi2D-omp

omp-scan: omp-scan.cpp
	$(CXX) $(CXXFLAGS) omp-scan.cpp -o omp-scan

clean:
	rm -f gs2D-omp jacobi2D-omp omp-scan
