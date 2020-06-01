#include "v_utilities.h"
#include "game.h"

int main() {

    int fd_board = open(FILE_BOARD, MODES);

    // User* user = init_game(1);

    int x, y;

    inputCoordinates(BUFFER);

    getCoordinates(BUFFER, &x, &y);

    printf("%d, %d\n", x, y);

    // board_print(user, 1, fd_board);

    // get_board(fd_board);
    // get_board(fd_board);
    // get_board(fd_board);
    
    // board_print(user, 1, fd_board);

    // get_board(fd_board);

    // board_print(user, 1, fd_board);

    // get_board(fd_board);


    // printf("%s\n", BUFFER_BOARD);

    // write(fd_board, BUFFER_BOARD, strlen(BUFFER_BOARD));

    close(fd_board);
}
