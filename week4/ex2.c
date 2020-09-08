#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*  In parenthesis I've identifiers of the process(not PID)
 *                             a.out(0)
 *                  /                               \
 *              a.out(0)                            a.out(1)
 *      /                   \                     /             \
 *  a.out(0)                a.out(2)            a.out(1)            a.out(3)
 * /        \               /      \        /           \       /           \
 * a.out(0) a.out(4)    a.out(2) a.out(5)   a.out(1) a.out(6)   a.out(3) a.out(7)
 *
 * Overall, we will have 8 running processes
 */

int main(void) {
    for (int i = 0; i < 3; ++i) {
        fork();
    }
    sleep(5);
    return EXIT_SUCCESS;
}
