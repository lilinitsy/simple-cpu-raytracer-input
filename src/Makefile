CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall

all: cppinput cinput
clean:
	rm -f *.o *.h.gch cppinput cinput

.PHONY: all clean test

cppinput: cppinput.o
	$(CXX) $(LDFLAGS) -o $(@) $(^)

cinput: cinput.o
	$(CXX) $(LDFLAGS) -o $(@) $(^)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)