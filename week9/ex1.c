#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint32_t

struct page_entry {
    int is_free;      // indicates whether the page is in use
    int page_id;      // unique identifier of the page, used for differentiating pages
    int referenced;   // reference bit. 1 means that the page was referenced in the last tick
    uint32_t counter; // Aging counter
};

// return index of the page in a page table if its in a page table
// return page_table_size otherwise
int page_table_contains(struct page_entry *page_table, int page_table_size, int page_id) {
    for (int i = 0; i < page_table_size; ++i) {
        if (page_table[i].page_id == page_id && !page_table[i].is_free) {
            return i;
        }
    }
    return page_table_size;
}

// Returns index of the free page in a page table, if such page exists
// returns page_table_size otherwise
int page_table_get_free_page(struct page_entry *page_table, int page_table_size) {
    for (int i = 0; i < page_table_size; ++i) {
        if (page_table[i].is_free) {
            return i;
        }
    }
    return page_table_size;
}

// inserts the page into page table
void page_table_fill_entry(struct page_entry *page, int page_id) {
    page->is_free = 0;
    page->counter = 0;
    page->referenced = 1;
    page->page_id = page_id;
}

// Return the index of the page to be evicted
int aging(struct page_entry *page_table, int page_table_size) {
    int candidate_id = 0;
    for (int i = 1; i < page_table_size; ++i) {
        if (page_table[i].counter < page_table[candidate_id].counter) {
            candidate_id = i;
        } else if (page_table[i].counter == page_table[candidate_id].counter &&
                   page_table[candidate_id].referenced && !page_table[i].referenced) {
            candidate_id = i;
        }
    }

    return candidate_id;
};

int main(int argc, char *argv[]) {
    // Checking input
    if (argc != 3) {
        printf("Usage: ./ex1 [page frames number] [counters refresh interval]\n");
        return EXIT_FAILURE;
    }

    // Reading and validating parameters
    int page_frames_number, counters_refresh_interval;
    page_frames_number = atoi(argv[1]);
    if (page_frames_number < 1) {
        perror("ERROR: page frames number must be a positive integer number\n");
        return EXIT_FAILURE;
    }
    counters_refresh_interval = atoi(argv[2]);
    if (counters_refresh_interval < 1) {
        perror("ERROR: counters refresh interval must be a positive integer number\n");
        return EXIT_FAILURE;
    }

    // Printing configuration
    printf("Configuration:\n\tNumber of page frames:%d\n\tCounters refresh interval: "
           "%d\n\n",
           page_frames_number, counters_refresh_interval);

    // Creating the page table
    struct page_entry *page_table = malloc(sizeof(struct page_entry) * page_frames_number);
    for (int i = 0; i < page_frames_number; ++i) {
        page_table[i].is_free = 1;
    }

    // Opening input file with sequence of page references
    FILE *in = fopen("input.txt", "read");
    if (in == NULL) {
        perror("ERROR: Can't open input.txt file\n");
        return EXIT_FAILURE;
    }

    int last_page_id;
    int hit = 0;
    int miss = 0;
main_loop:
    while (!feof(in)) {
        for (int i = 0; i < counters_refresh_interval; ++i) {
            fscanf(in, "%d", &last_page_id);
            // check if we haven't managed to read smth from the file
            if (feof(in)) {
                goto main_loop; // I wish there be a labeled break, but it isn't about the C
                                // language:(
            }

            // Checking if the page is in a page table
            int page_table_index =
                page_table_contains(page_table, page_frames_number, last_page_id);
            if (page_table_index < page_frames_number) {
                // Reference the page
                page_table[page_table_index].referenced = 1;
                ++hit;
            } else {
                // Update miss counter
                ++miss;
                // Handle page fault
                // 1. if there is a free page - just use it
                int free_page_id = page_table_get_free_page(page_table, page_frames_number);
                if (free_page_id < page_frames_number) {
                    page_table_fill_entry(&page_table[free_page_id], last_page_id);
                    continue;
                }
                // 2. Run aging
                int evicted_page_id = aging(page_table, page_frames_number);
                // 3. "Load" new page
                page_table_fill_entry(&page_table[evicted_page_id], last_page_id);
            }
        }

        // Update counters
        for (int i = 0; i < page_frames_number; ++i) {
            // 1. Shift counter to the right by one bit
            page_table[i].counter >>= 1;
            // 2. Add R bit to the leftmost position
            page_table[i].counter |= (page_table[i].referenced << 31);
            // 3. Reset R bit
            page_table[i].referenced = 0;
        }
    };

    // Print hit/miss ratio
    printf("Hit/Miss ratio: %f\n", ((double)hit) / miss);
    printf("%d\n", hit);
    printf("%d\n", miss);

    free(page_table);
    fclose(in);
    return EXIT_SUCCESS;
}
