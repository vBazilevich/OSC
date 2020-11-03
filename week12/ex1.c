#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int args, char *argc[]) {
    int rand = open("/dev/random", O_RDONLY);
    if (rand == -1) {
        perror("ERROR: Can not access /dev/random\n");
        return EXIT_FAILURE;
    }

    char buffer[20];
    read(rand, buffer, 20);

    // just in case if /dev/random produces 0 byte
    for (int i = 0; i < 20; ++i) {
        printf("%c", buffer[i]);
    }

    close(rand);
    return 0;
}
