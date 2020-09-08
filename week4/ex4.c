#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// custom imlementation. Reads from stdin until \n or EOF reached
// dynamically allocates buffer, thus we have to call free when we finish working with buffer
char *read_line() {
    char *buffer = NULL;
    int buff_size = 0;
    int c = getchar();
    while (c != '\n' && c != EOF) {
        ++buff_size;
        buffer = realloc(buffer, buff_size * sizeof(char));
        if (buffer == NULL) {
            perror("ERROR: Can't allocate memory for buffer\n");
            exit(EXIT_FAILURE);
        }
        buffer[buff_size - 1] = c;
        c = getchar();
    }
    buffer = realloc(buffer, (buff_size + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("ERROR: Can't allocate memory for buffer\n");
        exit(EXIT_FAILURE);
    }
    buffer[buff_size] = '\0';
    return buffer;
}

// splits comand to words by spaces
char **tokenize(char *cmd) {
    char **tokens = NULL;
    size_t tokens_count = 0;
    char *delims = " \t";
    char *token = strtok(cmd, delims);
    while (token != NULL) {
        ++tokens_count;
        tokens = realloc(tokens, sizeof(char *) * tokens_count);
        tokens[tokens_count - 1] = token;
        token = strtok(NULL, delims);
    }
    tokens = realloc(tokens, sizeof(char *) * (tokens_count + 1));
    tokens[tokens_count] = NULL;
    return tokens;
}

int main(void) {
    char *cmd;
    bool terminated = false;
    while (!terminated) {
        // printing prompt
        printf("->> ");
        // reading command
        cmd = read_line();

        if (strncmp(cmd, "exit", 4) == 0) {
            terminated = true;
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                char **args = tokenize(cmd);
                execvp(args[0], args);
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                perror("ERROR: Can't fork process\n");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
            }
        }
        free(cmd);
    }
    return EXIT_SUCCESS;
}
