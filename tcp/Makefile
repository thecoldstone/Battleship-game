CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

BOARD = ../src/board.c 
SHIP  = ../src/ship.c 
INIT_SHIPS = ../src/ship_setup.c
BATTLESHIP = ../src/battleship.c
USER = ../src/user.c
IO_HANDLER = ../src/io_handler.c

V_GAME = ../v_semaphores/game.c

GAME = $(BOARD) $(SHIP) $(INIT_SHIPS) $(BATTLESHIP) $(USER) $(IO_HANDLER) $(V_GAME)

TCP = tcp_utilities.c

build:
	$(CC) $(CFLAGS) -o server server.c $(GAME) $(TCP)

clean:
	rm server