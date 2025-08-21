# idk how to do makefiles properly
# This stopped working as soon as I tried to add the spaceship operator (<=>) to Rationals

default_target: main

CXX: g++
CXXFLAGS: -Wall -fsanitize=address -fsanitize=undefined -std=c++20
# CPPFLAGS = -Wall -Wextra -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op \
#            -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 \
#            -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector \
#            -O2 --std=c++20 -g

main: main.o
	$(CXX) $(CXXFLAGS) main.o calculator.o expressions.o rational.o -o calculator
#	rm *.o

main.o: main.cpp calculator.o
	$(CXX) -c main.cpp -o main.o

calculator.o: calculator.cpp calculator.h expressions.o
	$(CXX) -c calculator.cpp -o calculator.o

expressions.o: expressions.cpp expressions.h rational.o
	$(CXX) -c expressions.cpp -o expressions.o

rational.o: objects/rational.cpp objects/rational.h
	$(CXX) -c objects/rational.cpp -o rational.o
