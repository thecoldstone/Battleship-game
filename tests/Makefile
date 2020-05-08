CC = gcc
CFLAGS =  -std=c99 -g -Werror -Wextra -pedantic
SRC = *.c
OBJ = board_quadtree

build:
	$(CC) $(CFLAGS) -o $(OBJ)  $(SRC)

ship:
	$(CC) $(CFLAGS) -o ship ship.c
		
clean:
	rm ship
	rm -rf *.dSYM