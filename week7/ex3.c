#include <stdlib.h>
#include <stdio.h>
#include <time.h>  // needed for initializing srand

int main() {
    // Allows you to generate random number
    srand(time(NULL));

    // Allows user to specify the original array size, stored in variable n1.
    printf("Enter original array size:");
    int n1 = 0;
    scanf("%d", &n1);

    // Create a new array of n1 ints
    /* We have to allocate the memory for the array. Here I use malloc, as it will be
                        more efficient than calloc in this context. Malloc takes size of memory to
       be allocated in bytes, that is why I multiply n1 by size of integer. I explicitly
                        cast void* produced by malloc to int*.
    */

    int* a1 = (int*)malloc(sizeof(int) * n1);
    int i;
    for (i = 0; i < n1; i++) {
        // Set each value in a1 to 100
        /*Compiler knows that a1 is a pointer to integer, thus integers in a memory block associated
         * with this pointer can be accessed using square brackets notation. In pointer arithmetics
         * it is equivalent to *(a1 + i * sizeof(int))*/
        a1[i] = 100;

        // Print each element out (to make sure things look right)
        /* Accessing ith element of a1 using brackets notation*/
        printf("%d ", a1[i]);
    }

    // User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2);

    // Dynamically change the array to size n2
    a1 = realloc(a1, sizeof(int) * n2); /* reallocating memory*/

    // If the new array is a larger size, set all new members to 0. Reason: dont want to use
    // uninitialized variables.
    if (n2 > n1) {  //
        // n1 is the index of the first undefined array element
        for (int i = n1; i < n2; ++i) {
            a1[i] = 0;
        }
    }

    for (i = 0; i < n2; i++) {
        // Print each element out (to make sure things look right)
        printf("%d ", a1[i]);  // just indexating elements
    }
    printf("\n");

    // Done with array now, done with program :D
    free(a1);  // I dislike leaving a garbage;)
    return 0;
}
