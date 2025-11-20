#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 64

int main(void)
{

    char line[MAX_LINE_LENGTH];
    char *args[MAX_ARGS];

    while(1)
    {
        printf("k-shell> ");

        if(fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
        {
            printf("\nGoodbye Sir/Madam!\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        int i = 0;
        char *token = strtok(line, " \t");

        while(token != NULL)
        {
            args[i] = token;
            i++;

            token = strtok(NULL, " \t");
        }

        args[i] = NULL;

        printf("DEBUG: Found %d tokens:\n", i);
        for(int j = 0; j < i; j++)
        {
            printf("  args[%d]: %s\n", j, args[j]);
        }

    }


    return 0;
}