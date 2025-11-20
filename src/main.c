#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/shell.h"

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 64

int main(void) {
    char line[MAX_LINE_LENGTH];
    char *args[MAX_ARGS];
    int status = 1;

    while (status) {

        k_shell_print_prompt();

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }
        line[strcspn(line, "\n")] = 0;

        int i = 0;
        char *token = strtok(line, " \t");
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            status = k_shell_exit(args);
        } 
        else if (strcmp(args[0], "help") == 0) {
            status = k_shell_help(args);
        } 
        else if (strcmp(args[0], "cd") == 0) {
            status = k_shell_cd(args);
        } 
        else if (strcmp(args[0], "clear") == 0) {
            status = k_shell_clear(args);
        }
        else if (strcmp(args[0], "env") == 0) {
            status = k_shell_env(args);
        }
        else if (strcmp(args[0], "pwd") == 0) {
            status = k_shell_pwd(args);
        }
        else if (strcmp(args[0], "echo") == 0) {
            status = k_shell_echo(args);
        }
        else if (strcmp(args[0], "whoami") == 0) {
            status = k_shell_whoami(args);
        }
        else if (strcmp(args[0], "type") == 0) {
            status = k_shell_type(args);
        }
        else {
            pid_t pid = fork();
            if (pid == 0) {
                if (execvp(args[0], args) == -1) {
                    perror("k-shell");
                }
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                perror("k-shell");
            } else {
                wait(NULL);
            }
        }
    }
    return 0;
}