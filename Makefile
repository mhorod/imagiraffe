SOURCE = Source/*.cpp main.cpp
HEADERS = -IHeaders -IPerlinNoise

target:
	g++ -O3 -std=c++2a ${HEADERS} ${SOURCE} -omain `libpng-config --ldflags`

debug:
	g++ -g -std=c++2a ${HEADERS} ${SOURCE} -omain `libpng-config --ldflags`

