#include <stdio.h>
#include <stdlib.h>

void print_layer(int n, int level) {
    int offset = level;
    int midpoint = n - 1;
    for (int i = 0; i < 2 * n; ++i) {
        if (i >= midpoint - offset && i <= midpoint + offset) {
            putchar('*');
        } else {
            putchar(' ');
        }
    }
    putchar('\n');
}

void print_triangle(int n) {
    if (n < 0) {
        fprintf(stderr, "ERROR: Cannot create a triangle of negative height\n");
        exit(-1);
    }
    for (int level = 0; level < n; ++level) {
        print_layer(n, level);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <n>\n");
        return 0;
    }
    int n;
    sscanf(argv[1], "%d", &n);

    print_triangle(n);
    return 0;
}
