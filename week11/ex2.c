#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 128

int main(int argc, char *argv[]) {
    char buf[BUF_SIZE];
    setvbuf(stdout, buf, _IOLBF, BUF_SIZE);
    printf("H");
    sleep(1);
    printf("E");
    sleep(1);
    printf("L");
    sleep(1);
    printf("L");
    sleep(1);
    printf("O");
    sleep(1);
    printf("\n");
    return 0;
}
