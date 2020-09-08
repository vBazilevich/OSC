#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * In the output of this program we will see interleaving messages both from child and from parent
 * processes. Parent & child processes have different pids. Here process of context switching is
 * illustrated. Moreover, it shows that parent and child processes have their own stacks.
 * */

int main(void) {
    int n;
    pid_t child_pid = fork();
    for (n = 0; n < 30; ++n) {
        if (child_pid == 0) {
            printf("Hello from child process. [%d - %d]\n", getpid(), n);
        } else {
            printf("Hello from parent process. [%d - %d]\n", getpid(), n);
        }
    }
    return EXIT_SUCCESS;
}
