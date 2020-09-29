#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long int N = -1;
    printf("Input N: ");
    scanf("%ld", &N);

    if (N <= 0) {
        perror("Error: the number of elements must be positive\n");
        return EXIT_FAILURE;
    }

    // Malloc is used as in this case it gives higher performance as I don't need to nullify the
    // memory
    unsigned int *arr = (unsigned int *)malloc(sizeof(unsigned int) * N);
    if (arr == NULL) {
        perror("Error: Can't allocate required memory\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < N; ++i) {
        arr[i] = i;
    }

    for (size_t i = 0; i < N; ++i) {
        printf("arr[%lu] = %d\n", i, arr[i]);
    }

    free(arr);
    return EXIT_SUCCESS;
}
