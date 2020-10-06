#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
    Observations based on vmstat output:
    * From the very beginning only size of free memory is affected, no swap used. swpd decreses.
    * After some time si takes non-zero value - memory is swapped in from the swap space
    * Sometimes so also takes non-zero values - memory is swapped out to the swap space
    All in all, we can see how pages are swapped from and out of the swap space
*/

int main(int args, char *argv[]) {
    const int execution_duration = 10;  // 10 seconds
    size_t alloc_size = 1 << 30;    // 1 GB
    char *allocated_blocks[execution_duration];
    for (int t = 0; t < execution_duration; ++t) {
        // allocate 10 mb
        char *buffer = (char *)malloc(alloc_size);
        // fill with zeros
        memset(buffer, 0, alloc_size);
        // sleep
        sleep(1);
        allocated_blocks[t] = buffer;
    }

    for (int i = 0; i < execution_duration; ++i) {
        free(allocated_blocks[i]);
    }
    return 0;
}
