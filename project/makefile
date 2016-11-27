CCXX=g++
CCXXFLAGS=-std=c++14 -Wall -Werror -pedantic -Weffc++

default: setup clean obj
	$(CCXX) $(CCXXFLAGS) -O3 -o bin/interpreter main.cpp *.o

debug: debugObj
	$(CCXX) $(CCXXFLAGS) -g -o bin/dInterpreter main.cpp *.o

debugObj:
	$(CCXX) $(CCXXFLAGS) -c -g src/*.cpp

obj:
	$(CCXX) $(CCXXFLAGS) -c src/*.cpp

clean:
	-rm *.o

setup:
	mkdir -p bin
