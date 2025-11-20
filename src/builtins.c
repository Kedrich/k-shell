#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/shell.h"

// --- COLORS ---
#define COLOR_RESET   "\033[0m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_RED     "\033[1;31m" // NEW: Defined Red for the Heart and D

// Fix for 'environ' error
extern char **environ; 

// Function to print the prompt
void k_shell_print_prompt(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s%s >%s ", COLOR_CYAN, cwd, COLOR_RESET);
    } else {
        printf("%sk-shell >%s ", COLOR_CYAN, COLOR_RESET);
    }
}

// Built-in: cd
int k_shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("k-shell");
        }
    }
    return 1;
}

// Built-in: help (UPDATED DESIGN)
int k_shell_help(char **args) {
    printf("\n");
    // K is GREEN, Heart and D are RED
    printf("%s  _  __  %s%s   _   _     ____   %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("%s | |/ /  %s%s  / \\ / \\   |  _ \\  %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("%s | ' /   %s%s  \\  V  /   | | | | %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("%s | . \\   %s%s   \\   /    | |_| | %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("%s |_|\\_\\  %s%s     v      |____/  %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    
    printf("\n");
    printf("  %s--- Welcome to K-SHELL ---%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("  Type program names and arguments, and hit enter.\n\n");
    
    printf("  %sBuilt-in Commands:%s\n", COLOR_GREEN, COLOR_RESET);
    printf("  %s%-10s%s : Change current directory\n", COLOR_CYAN, "cd", COLOR_RESET);
    printf("  %s%-10s%s : Exit the shell\n", COLOR_CYAN, "exit", COLOR_RESET);
    printf("  %s%-10s%s : Show this help menu\n", COLOR_CYAN, "help", COLOR_RESET);
    printf("  %s%-10s%s : Clear the terminal screen\n", COLOR_CYAN, "clear", COLOR_RESET);
    printf("  %s%-10s%s : List environment variables\n", COLOR_CYAN, "env", COLOR_RESET);
    printf("  %s%-10s%s : Show current path\n", COLOR_CYAN, "pwd", COLOR_RESET);
    printf("\n");
    return 1;
}

// Built-in: exit
int k_shell_exit(char **args) {
    printf("Goodbye, salamat!\n");
    return 0;
}

// Built-in: clear
int k_shell_clear(char **args) {
    printf("\033[H\033[2J\033[3J");
    return 1;
}

// Built-in: env
int k_shell_env(char **args) {
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
    return 1;
}

// Built-in: pwd
int k_shell_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("k-shell");
    }
    return 1;
}