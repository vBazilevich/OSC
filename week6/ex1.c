#include "helpers.h"

void schedule(processes_data *pd) {
    unsigned int tick = 0;
    // as the processes are sorted by arrival time, we can execute them moving sequentually in the
    // order of PIDs
    for (int i = 0; i < pd->processes_count; ++i) {
        if (tick < pd->AT[i]) {
            tick = pd->AT[i];
        }
        pd->WT[i] += tick - pd->LET[i];
        tick += pd->BT[i];
        pd->ET[i] = tick;
        pd->TAT[i] = pd->ET[i] - pd->AT[i];
    }
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
