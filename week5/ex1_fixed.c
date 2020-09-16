#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADS_NUMBER 32
#define BUF_SIZE 128

int turn = 0;

void *say_hello(void *args) {
    // reading thread id
    int thread_id = *(int *)args;

    // Busy waiting with strict alternation
    while (turn != thread_id);
    printf("Hello! I'm thread %d\n", thread_id);

    // Incrementing turn
    turn = (turn + 1) % THREADS_NUMBER;
    pthread_exit(EXIT_SUCCESS);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[THREADS_NUMBER];
    int thread_ids[THREADS_NUMBER];

    // spawning threads
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, &say_hello, (void *)&thread_ids[i]);
    }

    // joining threads
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        int *retval = malloc(sizeof(int));
        pthread_join(threads[i], (void **)&retval);
        free(retval);
    }
    return EXIT_SUCCESS;
}
