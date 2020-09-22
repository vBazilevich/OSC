#ifndef HELPERS_H
#define HELPERS_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

unsigned int max(int a, int b) { return (a > b) ? a : b; }
unsigned int min(int a, int b) { return (a < b) ? a : b; }

typedef struct {
    size_t processes_count;
    unsigned int *PID;   // PIDS, given by arrival time
    unsigned int *AT;    // arrival times
    unsigned int *BT;    // burst tiem
    unsigned int *ET;    // exit time
    unsigned int *TAT;   // turn around times
    unsigned int *WT;    // waitings times
    unsigned int *LET;   // last tick then process was stopped
    bool *executed;      // true, if process is already executed
    unsigned int completion_time;
} processes_data;

void unsigned_int_array_swap(unsigned int *arr, int i, int j) {
    unsigned int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
};

void processes_data_swap_entries(processes_data *pd, int i, int j) {
    unsigned_int_array_swap(pd->PID, i, j);
    unsigned_int_array_swap(pd->AT, i, j);
    unsigned_int_array_swap(pd->BT, i, j);
    unsigned_int_array_swap(pd->ET, i, j);
    unsigned_int_array_swap(pd->TAT, i, j);
    unsigned_int_array_swap(pd->WT, i, j);
    unsigned_int_array_swap(pd->LET, i, j);
}

processes_data *read_input(char *filename) {
    // opening input files
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        perror("ERROR: Can't open file\n");
        exit(EXIT_FAILURE);
    }

    // allocating memory for processes data
    processes_data *pd = (processes_data *)malloc(sizeof(processes_data));
    if (pd == NULL) {
        perror("ERROR: Can't allocate memory for processes data\n");
        exit(EXIT_FAILURE);
    }
    // reading number of processes
    fscanf(input, "%lu", &pd->processes_count);

    // allocating memory for the fields of processes_data
    pd->PID = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->PID == NULL) {
        perror("ERROR: Can't allocate memory for process ids\n");
        exit(EXIT_FAILURE);
    }
    pd->AT = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->AT == NULL) {
        perror("ERROR: Cant allocate memory for arrival times\n");
        exit(EXIT_FAILURE);
    }
    pd->BT = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->BT == NULL) {
        perror("ERROR: Cant allocate memory for burst times\n");
        exit(EXIT_FAILURE);
    }
    pd->ET = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->ET == NULL) {
        perror("ERROR: Cant allocate memory for exit times\n");
        exit(EXIT_FAILURE);
    }
    pd->TAT = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->TAT == NULL) {
        perror("ERROR: Cant allocate memory for turnaround times\n");
        exit(EXIT_FAILURE);
    }
    pd->WT = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->WT == NULL) {
        perror("ERROR: Cant allocate memory for waiting times\n");
        exit(EXIT_FAILURE);
    }
    pd->LET = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (pd->LET == NULL) {
        perror("ERROR: Can't allocate memory for last break time\n");
        exit(EXIT_FAILURE);
    }
    pd->executed = (bool *)malloc(sizeof(bool) * pd->processes_count);
    if (pd->executed == NULL) {
        perror("ERROR: Can't allocate memory for executed status\n");
        exit(EXIT_FAILURE);
    }
    // reading processes data
    for (size_t i = 0; i < pd->processes_count; ++i) {
        fscanf(input, "%u %u", &pd->AT[i], &pd->BT[i]);
        // sorting using insertion sort WRT arrival time
        int j = i;
        while (j > 0 && pd->AT[j] < pd->AT[j - 1]) {
            processes_data_swap_entries(pd, j, j - 1);
            --j;
        }
    }

    // assigning PIDs
    for (size_t i = 0; i < pd->processes_count; ++i) {
        pd->PID[i] = i;
        pd->WT[i] = 0;
        pd->LET[i] = pd->AT[i];
        pd->executed[i] = false;
    }

    fclose(input);
    return pd;
}

void free_processes_data(processes_data *pd) {
    free(pd->PID);
    free(pd->AT);
    free(pd->BT);
    free(pd->ET);
    free(pd->TAT);
    free(pd->WT);
    free(pd->LET);
    free(pd->executed);
}

float unsigned_int_array_compute_avg(unsigned int *arr, size_t elements_count) {
    float sum = 0;
    for (size_t i = 0; i < elements_count; ++i) {
        sum += arr[i];
    }
    return sum / elements_count;
}

void print_results(processes_data *pd) {
    printf("Report:\n");
    printf("Completion time: %u\n", pd->completion_time);
    printf("PID\tTurn around time\tWaiting time\n");
    for (size_t i = 0; i < pd->processes_count; ++i) {
        printf("%d\t%u\t\t\t%u\n", pd->PID[i], pd->TAT[i], pd->WT[i]);
    }
    printf("Average turnaround time: %f\n",
           unsigned_int_array_compute_avg(pd->TAT, pd->processes_count));
    printf("Average waiting time: %f\n",
           unsigned_int_array_compute_avg(pd->WT, pd->processes_count));
}

bool in_list(unsigned int *list, size_t size, unsigned int element) {
    for (size_t i = 0; i < size; ++i) {
        if (element == list[i]) {
            return true;
        }
    }
    return false;
}


#endif
