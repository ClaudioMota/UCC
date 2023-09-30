CC=gcc
CXX=g++
C_FLAGS=-fPIC -g
INCLUDE_PATH=-I. -ISource
DIRS=$(shell find Source/ -type d)
C_SOURCES=$(shell find Source/ -type f -iname "*.c")
CPP_SOURCES=$(shell find Source/ -type f -iname "*.cpp")
C_OBJECTS=$(foreach x, $(basename $(C_SOURCES)), build/$(x).o)
CPP_OBJECTS=$(foreach x, $(basename $(CPP_SOURCES)), build/$(x).o)

TARGET=Linux64
LINK= -static-libstdc++ -static-libgcc -static

all: build $(C_OBJECTS) $(CPP_OBJECTS)
	g++ $(C_OBJECTS) $(CPP_OBJECTS) $(LINK) -o build/UCC

clean:
	rm -r build

build:
	mkdir build
	cd build ; ls -la ; mkdir $(foreach x, $(DIRS), $(x)) ; cd ..

build/%.o : %.c
	$(CC) $(C_FLAGS) $(INCLUDE_PATH) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

build/%.o : %.cpp
	$(CXX) $(C_FLAGS) $(INCLUDE_PATH) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

