#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define LENGTH 1024
int main(int argc, char **argv){
    int len;
    char buf[LENGTH];
    int src, dest, ret = 0;
    struct stat info;
    if(argc < 3){
        printf("Wrong Command!\n");
        return 0;
    }
    stat(argv[1], &info);
    src = open(argv[1], O_RDONLY);
    if(!src){
        printf("Invalid path of source file!\n");
        return 0;
    }
    dest = open(argv[2], O_CREAT | O_RDWR);
    if(!dest){
        printf("Fail to create destination file!\n");
        return 0;
    }
    memset(buf, 0, LENGTH);
    while((len = read(src, buf, LENGTH)) > 0){
        buf[len] = 0;
        write(dest, buf, len);
        memset(buf, 0, LENGTH);
    }
    chmod(argv[2], info.st_mode);
    close(src);
    close(dest);
    return 0;
}
