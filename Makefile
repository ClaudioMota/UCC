CC=gcc
CXX=g++
C_FLAGS=-Wall -fPIC -g -D _MALLOC=new -D _FREE=delete
INCLUDE_PATH=-I. -Isource
DIRS=$(shell find source/ -type d)
C_SOURCES=$(shell find source/ -type f -iname "*.c")
C_OBJECTS=$(foreach x, $(basename $(C_SOURCES)), build/$(x).o)

TARGET=Linux64
LINK= -static-libgcc -static

all: build $(C_OBJECTS)
	g++ $(C_OBJECTS) $(LINK) -o build/ucc

clean:
	rm -r build

build:
	mkdir build
	cd build ; ls -la ; mkdir $(foreach x, $(DIRS), $(x)) ; cd ..

build/%.o : %.c
	$(CC) $(C_FLAGS) $(INCLUDE_PATH) -c $(CFLAGS) $< -o $@
