CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2
LDFLAGS=
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

test: $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o test

depend: .depend

.depend: $(SRCS)
	rm -f .depend
	$(CXX) $(CXXFLAGS) -MM $^ -o .depend;

clean:
	$(RM) $(OBJ)

dist-clean: clean
	$(RM) *~ .depend

include .depend
