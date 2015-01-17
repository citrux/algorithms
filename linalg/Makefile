CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2
LDFLAGS=
SOURCES=linalg.cpp solvers.cpp test.cpp

OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

test: $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.d: %.cpp
	@set -e; $(CXX) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@

clean:
	$(RM) test $(OBJS) $(DEPS) *~

-include $(DEPS)
