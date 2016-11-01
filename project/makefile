compiler=clang++
flags=-std=c++11 -Wall -Werror -pedantic

default: clean obj
	$(compiler) $(flags) -o bin/compiler main.cpp *.o

obj:
	$(compiler) $(flags) -c src/*.cpp

clean:
	-rm *.o

