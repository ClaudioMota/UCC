CC=gcc
C_FLAGS=-Wall -Werror -fPIC -g -D _MALLOC=new -D _FREE=delete
INCLUDE_PATH=-I. -Isource
DIRS=$(shell find source/ -type d)
TEST_DIRS=$(shell find tests/ -type d)
C_SOURCES=$(shell find source/ -type f -iname "*.c" | grep -v 'main.c')
C_TEST_SOURCES=$(shell find tests/ -type f -iname "*.c")
C_OBJECTS=$(foreach x, $(basename $(C_SOURCES)), build/$(x).o)
C_TEST_OBJECTS=$(foreach x, $(basename $(C_TEST_SOURCES)), build/$(x))

TARGET=Linux64
LINK= -static-libgcc -static

ucc: build
	gcc $(C_FLAGS) $(INCLUDE_PATH) source/main.c $(C_OBJECTS) $(LINK) -o build/ucc

build: prepare $(C_OBJECTS)

build_all: build $(C_TEST_OBJECTS)

prepare:
	mkdir -p build
	cd build ; ls -la ; mkdir -p $(foreach x, $(DIRS), $(x)) ; cd ..
	cd build ; ls -la ; mkdir -p $(foreach x, $(TEST_DIRS), $(x)) ; cd ..

build/%.o : %.c
	$(CC) $(C_FLAGS) $(INCLUDE_PATH) -c $(CFLAGS) $< -o $@

build/tests/%: tests/%.c
	$(CC) $(C_FLAGS) $(INCLUDE_PATH) -Itests $(C_OBJECTS) $< -o $@

test: build_all
	build/tests/test

clean:
	rm -r build
