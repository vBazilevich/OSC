#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

pthread_cond_t buffer_is_empty;
pthread_cond_t buffer_is_full;
pthread_mutex_t
    count_mutex;  // used only in pthread_cond_wait. Locks right before it & unlocks right after it

int buffer[BUFFER_SIZE];
int buffer_counter = 0;
int items_produced = 0;

void *producer(void *args) {
    while (1) {
        // Generating new item
        int item = items_produced++;
        usleep(20);  // kind of intensive computations, w/o it locks after first iterations
        // Checking if there is a place on stack
        if (buffer_counter == BUFFER_SIZE) {
            printf("PRODUCER goes to sleep\n");

            // Sleep
            pthread_mutex_lock(&count_mutex);
            pthread_cond_wait(&buffer_is_empty, &count_mutex);
            pthread_mutex_unlock(&count_mutex);

            printf("PRODUCER wakes up\n");
        }
        // Putting number on common stack
        buffer[buffer_counter] = item;
        // Incrementing counter
        ++buffer_counter;
        // If buffer was empty, wakeup the consumer
        if (buffer_counter == 1) {
            pthread_cond_signal(&buffer_is_full);
        }
    }
    pthread_exit(EXIT_SUCCESS);
    return NULL;
}

void *consumer(void *args) {
    while (1) {
        // If buffer is empty, go to sleep
        if (buffer_counter == 0) {
            printf("CONSUMER goes to sleep\n");
            pthread_mutex_lock(&count_mutex);
            pthread_cond_wait(&buffer_is_full, &count_mutex);
            pthread_mutex_unlock(&count_mutex);
            printf("CONSUMER wakes up\n");
        }

        // Taking last item
        int item = buffer[buffer_counter - 1];
        // Decrementing counter
        --buffer_counter;
        // Waking up producer if there is available slot in the stack
        if (buffer_counter == BUFFER_SIZE - 1) {
            pthread_cond_signal(&buffer_is_empty);
        }

        // working with item... Somehow... Really intensive computations
    }
    pthread_exit(EXIT_SUCCESS);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t producer_thread, consumer_thread;
    pthread_mutex_init(&count_mutex, NULL);
    pthread_create(&producer_thread, NULL, &producer, NULL);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);

    int *retval = malloc(sizeof(int));
    pthread_join(producer_thread, (void **)&retval);
    free(retval);

    return EXIT_SUCCESS;
}
