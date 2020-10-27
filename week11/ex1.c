#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int max(int a, int b) { return (a < b) ? b : a; };

int main(int argc, char *argv[]) {
    int inout = open("ex1.txt", O_RDWR);
    if (inout == -1) {
        perror("ERROR: Can't open file\n");
        return -1;
    }

    // Computing size of the resulting file and resizing it
    int size = strlen("This is a nice day");
    if (ftruncate(inout, size)) {
        perror("ERROR: Can't resize the file\n");
        return -1;
    };

    char *ptr = mmap(NULL, size, PROT_WRITE, MAP_SHARED, inout, 0);
    if (ptr == MAP_FAILED) {
        perror("ERROR: Mapping failed\n");
        return -1;
    }
    strncpy(ptr, "This is a nice day", size);

    if (munmap(ptr, size)) {
        perror("ERROR: Can't unmap the file\n");
        return -1;
    }
    close(inout);

    return 0;
}
