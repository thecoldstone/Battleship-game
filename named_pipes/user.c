#include "np_utilities.h"
#include "game.h"

int main() {
    int fd_shoot, fd_board;
    int GAME = 1;
    int READ = 0;
    int WRITE = 1;

    User *user = init_game(1);
    mkfifo(FILE_SHOOT, S_IFIFO | 0777);

    fprintf(stdout, "User 1\n");

    fd_board = open(FILE_BOARD, O_RDWR | O_CREAT, 0777);
    if(lseek(fd_board, 0, SEEK_SET) < 0)
        perror("lseek");
    if(write(fd_board, "\0", 1) < 0)
        perror("write");
    board_print(user->board, 1, fd_board);  
    close(fd_board);

    while(GAME) {
        
        while(WRITE) {
            // WRITE
            fd_shoot = open(FILE_SHOOT, O_WRONLY);

            fprintf(stdout, "Enter coordinates: ");
            fgets(BUFFER, sizeof(BUFFER), stdin);
            if(BUFFER[strlen(BUFFER) - 1] == '\n') {
                BUFFER[strlen(BUFFER) - 1] = '\0';
            } 
            write(fd_shoot, BUFFER, strlen(BUFFER)); 
            close(fd_shoot);

            WRITE = 0;
            READ = 0;
            GAME = 0;
        }

    //     // memset(buffer, 0, sizeof(buffer));
    //     strcpy(buffer, "exit");
    //     if(strcmp(buffer, "exit") == 0) {
    //             break;
    //     }
        
    //     // while(READ) {
            
    //     //     memset(buffer, 0, sizeof(buffer));

    //     //     fd = open(fifo, O_RDONLY);
    //     //     read(fd, buffer, sizeof(buffer));
    //     //     fprintf(stdout, "%s\n", buffer);
    //     //     close(fd);
    //     //     WRITE = 1;
    //     //     READ = 0;
    //     // }
        
    //     // if(strcmp(buffer, "exit") == 0) {
    //     //         break;
    //     // }
    }


    unlink(FILE_SHOOT);

    return 0;

}