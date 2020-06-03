#include "np_utilities.h"
#include "game.h"

int main() {
    int fd_shoot, fd_board;
    int GAME = 1;
    int READ = 1;
    int WRITE = 0; 
    char *buffer_board;

    User *user = init_game(2);
    mkfifo(FILE_SHOOT, 0777);

    fprintf(stdout, "User 2\n");

    fd_board = open(FILE_BOARD, O_RDWR);
    buffer_board = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_board, 0);

    if(buffer_board == MAP_FAILED)
        perror("mmap");

    close(fd_board);

    printf("%s\n", buffer_board);

    while(GAME) {
        
        while(READ) {

            fd_shoot = open(FILE_SHOOT, O_RDONLY);
            read(fd_shoot, BUFFER, sizeof(BUFFER));
            fprintf(stdout, "%s\n", BUFFER);
            close(fd_shoot);

            WRITE = 1;
            READ = 0;
            GAME = 0;
        }
        
    //     // memset(buffer, 0, sizeof(buffer));
    //     strcpy(buffer, "exit");
    //     if(strcmp(buffer, "exit") == 0) {
    //             break;
    //     }

    //     // while(WRITE) {
    //     //     fflush(0);
    //     //     fd = open(fifo, O_WRONLY);
    //     //     fprintf(stdout, "Enter coordinates: ");
    //     //     fgets(buffer, sizeof(buffer), stdin);
    //     //     if(buffer[strlen(buffer) - 1] == '\n') {
    //     //         buffer[strlen(buffer) - 1] = '\0';
    //     //     } 
    //     //     write(fd, buffer, strlen(buffer)); 
    //     //     close(fd);

    //     //     WRITE = 0;
    //     //     READ = 1;
    //     // }

    //     // if(strcmp(buffer, "exit") == 0){
    //     //         break;
    //     // }

    }
    
    munmap(buffer_board, SIZE);
    unlink(FILE_SHOOT);
    return 0;

}