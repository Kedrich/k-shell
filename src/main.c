#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 64

int main(void)
{

    char line[MAX_LINE_LENGTH];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("k-shell> ");

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
        {
            printf("\nGoodbye Sir/Madam!\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

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
            continue;
        
        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting k-shell....\n");
            break;
        }

        else if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                fprintf(stderr, "k-shell: expected argument to \"cd\"\n");
            }
            else
            {
                if(chdir(args[1]) != 0)
                {
                    perror("k-shell");
                }
            }
        }

        else
        {
            pid_t pid = fork();

            if (pid == 0)
            {
                if(execvp(args[0], args) == -1)
                {
                    perror("k-shell");
                }
                exit(EXIT_FAILURE);
            }
            else if (pid < 0)
                perror("k-shell");
            else
                wait(NULL);
        }
    }


    return 0;
}