#include "helpers.h"
// Round robin algorithm
// Can take one integer as an argument - quantum
// Default quantum = 1

void schedule(processes_data *pd, unsigned int quantum) {
    unsigned int *ready = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (ready == NULL) {
        perror("ERROR: Can't allocate memory for the list of ready processes");
        exit(EXIT_FAILURE);
    }
    size_t ready_count = 0;
    unsigned int tick = 0;
    unsigned int exited_processes = 0;
    while (exited_processes < pd->processes_count) {
        // add all ready not executed jobs to the ready list
        for (int proc_id = 0; proc_id < pd->processes_count; ++proc_id) {
            if (!pd->executed[proc_id] && pd->AT[proc_id] <= tick &&
                !in_list(ready, ready_count, proc_id)) {
                ready[ready_count] = proc_id;
                ++ready_count;
            }
        }
        if (ready_count == 0) {
            ++tick;
            continue;
        }

        // Execute the first one unless it finishes or its quantum goes to an end
        size_t pid_id = ready[0];
        pd->WT[pid_id] += tick - pd->LET[pid_id];
        unsigned int dt = min(quantum, pd->BT[pid_id]);
        pd->BT[pid_id] -= dt;
        tick += dt;
        if (pd->BT[pid_id] == 0) {
            pd->TAT[pid_id] = tick - pd->AT[pid_id];
            pd->ET[pid_id] = tick;
            pd->executed[pid_id] = true;
            // remove from queue
            for (int j = 0; j < ready_count - 1; ++j) {
                ready[j] = ready[j + 1];
            }
            --ready_count;
            ++exited_processes;
        } else {
            pd->LET[pid_id] = tick;
            // move to the end of the queue
            for (int j = 0; j < ready_count - 1; ++j) {
                ready[j] = ready[j + 1];
            }
            ready[ready_count - 1] = pid_id;
        }
    }
    free(ready);
    pd->completion_time = tick;
}

int main(int argc, char **argv) {
    processes_data *pd = read_input("processes.list");
    int quantum = 1;  // default value
    if (argc == 2) {
        quantum = atoi(argv[1]);
        if (quantum < 1) {
            perror("ERROR: Quantum must be integer positive number\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Running round-robin with quantum %u...\n", quantum);
    // running simulation
    schedule(pd, quantum);

    // printing report
    print_results(pd);
    // cleaning up
    free_processes_data(pd);
    free(pd);
    return 0;
}
