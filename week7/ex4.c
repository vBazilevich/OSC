#include <stdlib.h> // malloc and free
#include <malloc.h>  // malloc_usable_size
#include <string.h> // memcpy

void *my_realloc(void *ptr, size_t size) {
    // If ptr is null, do usual allocation
    if (ptr == NULL) {
        return malloc(size);
    }

    // If size if equal to 0, the call is equivalent to free
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_mem_block = malloc(size);

    // obtaining the size of the old allocation
    size_t old_size = malloc_usable_size(ptr);  // gnu extension
    // Copying data
    memcpy(new_mem_block, ptr, old_size);
    return new_mem_block;
}

int main(int argc, char *argv[]) {
    // Test 0: Null ptr and non-zero size
    int *p0 = NULL;
    p0 = my_realloc(p0, 11 * sizeof(int));
    printf("The size of memblock associated with p0 is %lu bytes\n", malloc_usable_size(p0));
    free(p0);

    // Test 1: Non-null ptr and 0 size
    int *p1 = malloc(sizeof(int) * 4);
    p1 = my_realloc(p1, 0);
    printf("%p\n", p1);

    // Test 2: Non-null ptr. Size increased
    int *p2 = malloc(2 * sizeof(int));
    p2[0] = 32;
    p2[1] = 41;
    size_t new_size = 4;
    p2 = my_realloc(p2, new_size * sizeof(int));
    for (int i = 0; i < new_size; ++i) {
        printf("%d\t", p2[i]);
    }
    printf("\n");
    free(p2);

    // Test 3: Non-null ptr. Size decreased
    int *p3 = malloc(sizeof(int) * 3);
    p3[0] = 1;
    p3[1] = 2;
    p3[2] = 3;
    new_size = 2;
    p3 = realloc(p3, new_size * sizeof(int));
    for (int i = 0; i < new_size; ++i) {
        printf("%d\t", p3[i]);
    }
    printf("\n");
    free(p3);
    return 0;
}
