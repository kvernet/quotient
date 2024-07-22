COMPILER = gcc
CFLAGS   = -O02 -Wall -Werror -Wextra
LDFLAGS  = -shared

LIB_NAME = quotient
BIN_NAME = exec


all: build

build: $(BIN_NAME).c $(LIB_NAME)
	mkdir -p bin
	$(COMPILER) $(CFLAGS) -o bin/$(BIN_NAME) $< -Isrc -Llib -l$(LIB_NAME) -Wl,-rpath=`pwd`/lib

LIB_SRCS = src/quotient.c

$(LIB_NAME): $(LIB_SRCS)
	mkdir -p lib
	$(COMPILER) $(CFLAGS) $(LDFLAGS) -o lib/lib$@.so $^ -Isrc

clean:
	rm -rf bin
	rm -rf lib

.PHONY: all clean $(LIB_NAME)
