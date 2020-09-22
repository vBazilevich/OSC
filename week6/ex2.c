#include "helpers.h"
// Shortest job first

void schedule(processes_data *pd) {
    unsigned int *ready = (unsigned int *)malloc(sizeof(unsigned int) * pd->processes_count);
    if (ready == NULL) {
        perror("ERROR: Can't allocate memory for the list of ready processes");
        exit(EXIT_FAILURE);
    }
    size_t ready_count = 0;
    unsigned int tick = 0;
    for (int i = 0; i < pd->processes_count; ++i) {
        // add all ready not executed jobs to the ready list
        for (int proc_id = 0; proc_id < pd->processes_count; ++proc_id) {
            if (!pd->executed[proc_id] && pd->AT[proc_id] <= tick &&
                !in_list(ready, ready_count, proc_id)) {
                // checking if it is in the queue already
                ready[ready_count] = proc_id;
                ++ready_count;
            }
        }

        // If there are no arrived jobs - increment clock and repeat
        if (ready_count == 0) {
            ++tick;
            --i;
            continue;
        }

        // Choose the shortest job to be executed
        size_t ready_id = 0;
        for (int j = 1; j < ready_count; ++j) {
            if (pd->BT[ready[j]] < pd->BT[ready[ready_id]]) {
                ready_id = j;
            }
        }
        size_t pid_id = ready[ready_id];

        // Execute this job
        pd->WT[pid_id] += tick - pd->LET[pid_id];
        tick += pd->BT[pid_id];
        pd->ET[pid_id] = tick;
        pd->TAT[pid_id] = pd->ET[pid_id] - pd->AT[pid_id];
        pd->executed[pid_id] = true;
        // remove this element from queue
        --ready_count;
        ready[ready_id] = ready[ready_count];
    }
    free(ready);
    pd->completion_time = tick;
}

int main(int argc, char **argv) {
    processes_data *pd = read_input("processes.list");

    // running simulation
    schedule(pd);

    // printing report
    print_results(pd);
    // cleaning up
    free_processes_data(pd);
    free(pd);
    return 0;
}
