#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char **argv){
	int ret = 0;
    if(argc < 3){
        printf("Wrong Command!\n");
        return 0;
    }
	ret = syscall(333, argv[1], argv[2]);
    if(ret == -1){
        printf("Invalid path of file!\n");
        return 0;
    }
    return 0;
}
