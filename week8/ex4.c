#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

int main(int args, char *argv[]) {
    const int execution_duration = 10;  // 10 seconds
    size_t alloc_size = 1 << 30;    // 1 GB
    char *allocated_blocks[execution_duration];
    for (int t = 0; t < execution_duration; ++t) {
        // allocate 10 mb
        char *buffer = (char *)malloc(alloc_size);
        // fill with zeros
        memset(buffer, 0, alloc_size);
        // print memory usage
        struct rusage res;
        getrusage(RUSAGE_SELF, &res);
        printf("Memory usage: %ld\n", res.ru_maxrss);
        // sleep
        sleep(1);
        allocated_blocks[t] = buffer;
    }

    for (int i = 0; i < execution_duration; ++i) {
        free(allocated_blocks[i]);
    }
    return 0;
}
