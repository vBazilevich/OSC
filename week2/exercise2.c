#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *user_string = NULL;
    size_t len = 0;

    // reading string
    getline(&user_string, &len, stdin);
    // printing in reverse order
    for (int i = strlen(user_string) - 1; i >= 0; --i) {
        putchar(user_string[i]);
    }
    putchar('\n');

    // getline allocated memory, because we provided a NULL pointer as its first argument
    free(user_string);
    return 0;
}
