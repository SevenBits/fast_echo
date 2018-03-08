CFLAGS=-std=c11 -Wall -Werror -Wextra -pedantic -O2 -pipe -march=native -mtune=native

all: fast_echo
fast_echo: fast_echo.o
	$(CC) $^ -o $@
