#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int in = open("ex1.txt", O_RDONLY);
    if (in == -1) {
        perror("ERROR: Can't open source file\n");
        return -1;
    }

    int out = open("ex1.memcpy.txt", O_RDWR);
    if (out == -1) {
        perror("ERROR: Can't open destination file\n");
        return -1;
    }

    struct stat st;
    fstat(in, &st);
    int size = st.st_size;

    char *ptr1 = mmap(NULL, size, PROT_READ, MAP_SHARED, in, 0);
    if (ptr1 == MAP_FAILED) {
        perror("ERROR: Can't map source file\n");
        return -1;
    }

    ftruncate(out, size);
    char *ptr2 = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, out, 0);
    if (ptr2 == MAP_FAILED) {
        perror("ERROR: Can't map destination file\n");
        return -1;
    }

    memcpy(ptr2, ptr1, size);

    munmap(ptr1, size);
    munmap(ptr2, size);
    close(in);
    close(out);
    return 0;
}
