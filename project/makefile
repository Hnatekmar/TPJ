CCXX=clang++
CCXXFLAGS=-std=c++14 -Wall -Werror -pedantic -Wno-c++98-compat -Weffc++

default: setup clean obj
	$(CCXX) $(CCXXFLAGS) -o bin/interpreter main.cpp *.o

debug: debugObj
	$(CCXX) $(CCXXFLAGS) -g -o bin/dInterpreter main.cpp *.o

debugObj:
	$(compiler) $(flags) -c -g src/*.cpp

obj:
	$(compiler) $(flags) -c src/*.cpp

clean:
	-rm *.o

setup:
	mkdir -p bin
