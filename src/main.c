#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256

int main(void)
{

    char line[MAX_LINE_LENGTH];

    while(1)
    {
        printf("k-shell> ");

        if(fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
        {
            printf("\nGoodbye Sir/Madam!\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        printf("DEBUG: You typed %s\n", line);
    }


    return 0;
}