CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2
LDFLAGS=
SOLVERS=linalg.cpp solvers.cpp test.cpp
EIGENS=vector.cpp matrix.cpp test_h.cpp

solvers:
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $(SOLVERS)

eigens:
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $(EIGENS)
