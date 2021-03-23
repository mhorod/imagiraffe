SOURCE = `find . -maxdepth 1 -name '*.cpp'`

debug:
	g++ -g -std=c++2a ${SOURCE} -omain `libpng-config --ldflags`
