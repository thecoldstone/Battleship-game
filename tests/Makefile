CC = gcc
CFLAGS =  -std=c99 -g -Werror -Wextra -pedantic

build:
	$(CC) $(CFLAGS) -o mmap_w mmap_w.c
	$(CC) $(CFLAGS) -o mmap_r mmap_r.c

clean:
	rm mmap_w
	rm mmap_r
	rm -rf *.dSYM