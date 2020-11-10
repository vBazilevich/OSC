#include <stdio.h>
#include <stdlib.h>

// returns 0 if all elements in row are less than or equal than corresponding entries in available
// returns 1 otherwise
int row_is_less(int *available, int *row, int n){
    for(int i = 0; i < n; ++i){
        if(row[i] > available[i]){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    // reading input file
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("ERROR: Can't open file input.txt\n");
        return EXIT_FAILURE;
    }

    // Reading R and P
    int R, P;
    fscanf(input, "%d %d", &R, &P);

    // reading existing vector
    int *existing = malloc(sizeof(int) * R);
    if (existing == NULL) {
        perror("ERROR: Can't allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < R; ++i) {
        fscanf(input, "%d", &existing[i]);
    }

    // reading available vector
    int *available = malloc(sizeof(int) * R);
    if (available == NULL) {
        perror("ERROR: Can't allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < R; ++i) {
        fscanf(input, "%d", &available[i]);
    }

    // reading current allocation matrix
    int **C = malloc(sizeof(int *) * P);
    if (C == NULL) {
        perror("ERROR: Can't allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int p = 0; p < P; ++p) {
        C[p] = malloc(sizeof(int) * R);
        if (C[p] == NULL) {
            perror("ERROR: Can't allocate memory\n");
            return EXIT_FAILURE;
        }

        for(int r = 0; r < R; ++r) {
            fscanf(input, "%d", &C[p][r]);
        }
    }

    // reading requests matrix
    int **Req = malloc(sizeof(int *) * P);
    if (Req == NULL) {
        perror("ERROR: Can't allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int p = 0; p < P; ++p) {
        Req[p] = malloc(sizeof(int) * R);
        if (Req[p] == NULL) {
            perror("ERROR: Can't allocate memory\n");
            return EXIT_FAILURE;
        }

        for(int r = 0; r < R; ++r) {
            fscanf(input, "%d", &Req[p][r]);
        }
    }
    // We don't need input anymore, so we can close it.
    fclose(input);

    // Main logic starts here
    // we have to keep track of the processes that are already finished
    int *finished = calloc(P, sizeof(int));
    for(int i = 0; i < P; ++i){
        // looking for the runnable process
        for (int j = 0; j < P; ++j) {
            if (!finished[j] && row_is_less(available, Req[j], R)) {
                fprintf(stderr, "Process %d succesfully terminate\n", j);
                // "free" resources
                for (int r = 0; r < R; ++r) {
                    available[r] += C[j][r];
                }
                // mark process as finished
                finished[j] = 1;
                break;
            }
        }
    }

    // detecting non-terminated process
    int deadlocked = 0;
    for (int i = 0; i < P; ++i) {
        if (!finished[i]) {
            ++deadlocked;
        }
    }

    FILE *output = fopen("output.txt", "w");
    if (deadlocked == 0) {
        fprintf(output, "no deadlock\n");
    } else {
        fprintf(output, "%d processes are in a deadlock\n", deadlocked);
    }
    fclose(output);
    free(existing);
    free(available);
    for (int i = 0; i < P; ++i) {
        free(C[i]);
        free(Req[i]);
    }
    free(C);
    free(Req);
    free(finished);
    return EXIT_SUCCESS;
}
