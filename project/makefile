compiler=clang++
flags=-std=c++11 -Wall -Werror -pedantic -Wno-c++98-compat -Weffc++

default: clean obj
	$(compiler) $(flags) -o bin/compiler main.cpp *.o

debug: debugObj
	$(compiler) $(flags) -g -o bin/compiler main.cpp *.o

debugObj:
	$(compiler) $(flags) -c -g src/*.cpp

obj:
	$(compiler) $(flags) -c src/*.cpp

clean:
	-rm *.o

