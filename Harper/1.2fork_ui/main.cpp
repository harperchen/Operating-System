#include <unistd.h>
#include <errno.h>
#include "head.h"

int main(int argc, char *argv[])
{

    pid_t pid_1;
    pid_1 = fork();
    if(pid_1 == -1) {
        perror("tile");
        return -1;
    }
    if(pid_1 > 0) {
        pid_t pid_2;
        pid_2 = fork();
        if(pid_2 == -1) {
            perror("tile");
            return -1;
        }
        if(pid_2 > 0) { //main
            left(argc, argv);
        }
        else if(pid_2 == 0){
            mid(argc, argv);
        }
    }
    else if(pid_1 == 0){
        right(argc, argv);
    }
    return 0;
}


