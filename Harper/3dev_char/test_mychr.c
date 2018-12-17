#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
int main(){
    int fd, size;
    char write_data[64] = "read and write test!";
    char read_data[64];
    fd = open("/dev/mychr0", O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("error open!\n");
        return 0;
    }
    printf("open /dev/mychr0 successfully!\n");
    size = write(fd, write_data, strlen(write_data));
    if(size == -1){
        perror("write error!\n");
        return 0;
    }
    printf("write data is %s\n", write_data);
    printf("User write size is %d\n", size);
    lseek(fd, 0, SEEK_SET);
    size = read(fd, read_data, strlen(write_data));
    if(size == -1){
        perror("read error!\n");
        return 0;
    }
    printf("User read size is %d\n", size);
    printf("read data is %s\n", read_data);
    sleep(30);
    close(fd);
    printf("close /dev/mychr0 successfully!\n");
    return 0;
}