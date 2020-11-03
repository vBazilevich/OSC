#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_FILES 8 // includin /dev/stdout

int main(int argc, char *argv[]) {
    int APPEND_MODE = 0; // by default, no append
    // according to specification, options must be given BEFORE files
    if (argc > 1 && strcmp(argv[1], "-a") == 0) {
        APPEND_MODE = 1;
    }

    // first arg - prog name. Then (possibly) -a flag
    // and finally up to MAX_FILES - 1 files to be opened
    if (argc > 1 + APPEND_MODE + MAX_FILES - 1) {
        perror("ERROR: Too much files.\n");
    }

    int files_count = argc - APPEND_MODE - 1;

    // file desctiptors
    int file_descriptors[MAX_FILES];
    // opening stdout
    file_descriptors[0] = open("/dev/stdout", O_WRONLY);
    if (file_descriptors[0] == -1) {
        perror("ERROR: Can not open /dev/stdout\n");
    }

    // openning provided files
    for (int i = 1; i <= files_count; ++i) {
        if (APPEND_MODE) {
            file_descriptors[i] = open(argv[1 + i], O_WRONLY | O_APPEND | O_CREAT,
                                       S_IRUSR | S_IWUSR);
        } else {
            file_descriptors[i] = open(argv[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        }
    }

    // opening stdin
    int inp = open("/dev/stdin", O_RDONLY);

    // reading from stdin
    char c;
    while (read(inp, &c, 1)) {
        for (int i = 0; i < 1 + files_count; ++i) {
            write(file_descriptors[i], &c, 1);
        }
    }

    // closing files
    for (int i = 0; i < 1 + files_count; ++i) {
        close(file_descriptors[i]);
    }
    close(inp);

    return 0;
}
