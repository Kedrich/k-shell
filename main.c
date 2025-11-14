#include <stdio.h>
#include <string.h> 

#define MAX_LINE_LENGTH 256

void menu()
{
    printf("Welcome to my K-Shell!\n");
    printf("Guides:\n");
    printf("1. Enter \"exit\" or \"Ctrl-Z\" to exit the program completely\n");
}

int main(void) {
    char line[MAX_LINE_LENGTH];

    menu();

    while (1) {
        printf("k-shell> ");

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {

            printf("\nGoodbye!\n");
            break;
        }

        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "exit") == 0) {
            printf("Exiting k-shell...\n");
            break;
        }

        printf("You typed: %s\n", line);
    }

    return 0;
}