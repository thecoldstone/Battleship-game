CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror

BOARD = ../src/board.c 
SHIP  = ../src/ship.c 
INIT_SHIPS = ../src/ship_setup.c
BATTLESHIP = ../src/battleship.c
USER = ../src/user.c
IO_HANDLER = ../src/io_handler.c
GAME = $(BOARD) $(SHIP) $(INIT_SHIPS) $(BATTLESHIP) $(USER) $(IO_HANDLER) game.c

V_SYSTEM_UTILITIES = v_utilities.c

build:
	$(CC) $(CFLAGS) -o user user.c $(GAME) $(V_SYSTEM_UTILITIES)
	$(CC) $(CFLAGS) -o user2 user2.c $(GAME) $(V_SYSTEM_UTILITIES)

clean:
	rm user
	rm user2 
	rm shoot.txt
	rm board.txt