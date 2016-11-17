compiler=clang++
flags=-std=c++11 -Wall -Werror -pedantic -Wno-c++98-compat -Weffc++

default: clean
	make -C ../project
	$(compiler) $(flags) -o bin/tests main.cpp ../project/*.o
	./bin/tests

clean:
	-rm bin/*
