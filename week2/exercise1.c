#include <stdio.h>   // printf
#include <limits.h>  // INT_MAX
#include <float.h>   // FLT_MAX, DBL_MAX

int main(int argc, char *argv[]) {
    // Decalring variables and initializing them with maximal values
    int i = INT_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;

    // Printing out size of variables and their maximal values
    printf("Int has size %lu bytes and its maximal value is %d\n", sizeof(i), i);
    printf("Float has size %lu bytes and its maximal value is %f\n", sizeof(f), f);
    printf("Double has size %lu bytes and its maximal value is %f\n", sizeof(d), d);
    return 0;
}
