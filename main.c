#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 64

void k_shell_help() {
    printf("--- k-shell: A Simple Shell in C ---\n");
    printf("Created by Kedrich.\n\n");
    printf("These are the built-in commands:\n");
    printf("  help      - Show this help message.\n");
    printf("  exit      - Exit the shell (or use Ctrl+Z).\n");
    printf("\n");
    printf("For other commands, k-shell will try to execute them as external programs.\n");
}

int main(void) {
    char line[MAX_LINE_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        printf("k-shell> ");

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {

            printf("\nGoodbye!\n");
            break;
        }

        line[strcspn(line, "\r\n")] = 0;

        int i = 0;
        char *token = strtok(line, " \t");
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] == NULL)
        {
            continue;
        }

        if (strcmp(args[0], "help") == 0)
        {
            k_shell_help();
        }
        else if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting k-shell...\n");
            break;
        }
        else
        {
            printf("Tokens for external commands:\n");
            for(int j = 0; j < i; j++)
            {
                printf(" arg[%d]: %s\n", j, args[j]);
            }
        }
    }

    return 0;
}