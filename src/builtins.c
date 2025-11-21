#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include "../include/shell.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_RED     "\033[1;31m"

extern char **environ; 

void k_shell_print_prompt(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s%s >%s ", COLOR_CYAN, cwd, COLOR_RESET);
    } else {
        printf("%sk-shell >%s ", COLOR_CYAN, COLOR_RESET);
    }
}

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

int k_shell_help(char **args) {
    // 1. If user typed "help" (no arguments), show the main menu
    if (args[1] == NULL) {
        printf("\n");
        printf("%s  _  __  %s%s   _   _     ____   %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
        printf("%s | |/ /  %s%s  / \\ / \\   |  _ \\  %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
        printf("%s | ' /   %s%s  \\  V  /   | | | | %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
        printf("%s | . \\   %s%s   \\   /    | |_| | %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
        printf("%s |_|\\_\\  %s%s     v      |____/  %s\n", COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
        
        printf("\n");
        printf("  %s--- Welcome to K-SHELL ---%s\n", COLOR_YELLOW, COLOR_RESET);
        printf("  Type program names and arguments, and hit enter.\n");
        printf("  For specific information, type: %shelp <command>%s\n\n", COLOR_CYAN, COLOR_RESET);
        
        printf("  %sBuilt-in Commands:%s\n", COLOR_GREEN, COLOR_RESET);
        printf("  %-10s %-10s %-10s %-10s\n", "cd", "exit", "help", "clear");
        printf("  %-10s %-10s %-10s %-10s\n", "env", "pwd", "echo", "whoami");
        printf("  %-10s %-10s %-10s %-10s\n", "type", "export", "unset", "mkcd");
        printf("  %-10s %-10s %-10s %-10s\n", "kfetch", "touch", "rm", "calc");
        printf("\n");
        return 1;
    }

    // 2. If user typed "help <command>", show specific info
    printf("\n");
    if (strcmp(args[1], "cd") == 0) {
        printf("%sCommand:%s  cd\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Change the current working directory.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    cd <directory_path>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  cd /home/kedrich/projects\n", COLOR_GREEN, COLOR_RESET);
    } 
    else if (strcmp(args[1], "exit") == 0) {
        printf("%sCommand:%s  exit\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Close and exit the k-shell session.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    exit\n", COLOR_GREEN, COLOR_RESET);
    } 
    else if (strcmp(args[1], "help") == 0) {
        printf("%sCommand:%s  help\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Display information about builtin commands.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    help [command_name]\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "clear") == 0) {
        printf("%sCommand:%s  clear\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Clean the terminal screen and scrollback history.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    clear\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "env") == 0) {
        printf("%sCommand:%s  env\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  List all current environment variables.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    env\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "pwd") == 0) {
        printf("%sCommand:%s  pwd\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Print Working Directory (show where you are).\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    pwd\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "echo") == 0) {
        printf("%sCommand:%s  echo\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Display a line of text/string to the screen.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    echo <text>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  echo Hello World\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "whoami") == 0) {
        printf("%sCommand:%s  whoami\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Display the username of the current user.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    whoami\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "type") == 0) {
        printf("%sCommand:%s  type\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Identify if a command is a shell builtin or external program.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    type <command_name>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  type cd\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "export") == 0) {
        printf("%sCommand:%s  export\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Create or update an environment variable.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    export KEY=VALUE\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  export MY_NAME=Kedrich\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "unset") == 0) {
        printf("%sCommand:%s  unset\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Remove an environment variable.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    unset KEY\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  unset MY_NAME\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "mkcd") == 0) {
        printf("%sCommand:%s  mkcd\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Create a new directory and immediately enter it.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    mkcd <directory_name>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  mkcd my_new_project\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "kfetch") == 0) {
        printf("%sCommand:%s  kfetch\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Display system information and shell branding.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    kfetch\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "touch") == 0) {
        printf("%sCommand:%s  touch\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Create a new empty file.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    touch <filename>\n", COLOR_GREEN, COLOR_RESET);
    }
    else if (strcmp(args[1], "rm") == 0) {
        printf("%sCommand:%s  rm\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Delete a file permanently.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    rm <filename>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sWarning:%s  This action cannot be undone!\n", COLOR_RED, COLOR_RESET);
    }
    else if (strcmp(args[1], "calc") == 0) {
        printf("%sCommand:%s  calc\n", COLOR_CYAN, COLOR_RESET);
        printf("%sPurpose:%s  Perform basic arithmetic operations.\n", COLOR_YELLOW, COLOR_RESET);
        printf("%sUsage:%s    calc <num1> <operator> <num2>\n", COLOR_GREEN, COLOR_RESET);
        printf("%sExample:%s  calc 10 + 5\n", COLOR_GREEN, COLOR_RESET);
    }
    else {
        printf("Help: No manual entry for '%s'.\n", args[1]);
    }
    printf("\n");
    return 1;
}

int k_shell_exit(char **args) {
    printf("Goodbye, salamat!\n");
    return 0;
}

int k_shell_clear(char **args) {
    printf("\033[H\033[2J\033[3J");
    return 1;
}

int k_shell_env(char **args) {
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
    return 1;
}

int k_shell_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("k-shell");
    }
    return 1;
}

int k_shell_echo(char **args) {
    int i = 1;
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }
    printf("\n");
    return 1;
}

int k_shell_whoami(char **args) {
    char *user = getenv("USER");
    if (user != NULL) {
        printf("%s\n", user);
    } else {
        printf("Unknown user\n");
    }
    return 1;
}

int k_shell_type(char **args) {
    if (args[1] == NULL) {
        printf("type: expected argument\n");
        return 1;
    }

    if (strcmp(args[1], "cd") == 0 ||
        strcmp(args[1], "exit") == 0 ||
        strcmp(args[1], "help") == 0 ||
        strcmp(args[1], "clear") == 0 ||
        strcmp(args[1], "env") == 0 ||
        strcmp(args[1], "pwd") == 0 ||
        strcmp(args[1], "echo") == 0 ||
        strcmp(args[1], "whoami") == 0 ||
        strcmp(args[1], "type") == 0 ||
        strcmp(args[1], "export") == 0 ||
        strcmp(args[1], "unset") == 0 ||
        strcmp(args[1], "mkcd") == 0 ||
        strcmp(args[1], "kfetch") == 0 ||
        strcmp(args[1], "touch") == 0 ||
        strcmp(args[1], "rm") == 0 ||
        strcmp(args[1], "calc") == 0) {
            printf("%s is a shell builtin\n", args[1]);
    } 
    else {
        printf("%s is /usr/bin/%s\n", args[1], args[1]);
    }
    return 1;
}

int k_shell_export(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected argument \"KEY=VALUE\"\n");
        return 1;
    }

    char *equal_sign = strchr(args[1], '=');
    if (equal_sign == NULL) {
        fprintf(stderr, "k-shell: export format must be KEY=VALUE\n");
        return 1;
    }

    *equal_sign = '\0';
    char *key = args[1];
    char *value = equal_sign + 1;

    if (setenv(key, value, 1) != 0) {
        perror("k-shell");
    }

    return 1;
}

int k_shell_unset(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected argument\n");
        return 1;
    }

    if (unsetenv(args[1]) != 0) {
        perror("k-shell");
    }
    return 1;
}

int k_shell_mkcd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected directory name\n");
        return 1;
    }

    if (mkdir(args[1], 0755) != 0) {
        perror("k-shell");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        perror("k-shell");
    } else {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Created and entered %s\n", cwd);
    }
    
    return 1;
}

int k_shell_kfetch(char **args) {
    struct utsname sys_info;
    uname(&sys_info);

    printf("\n");
    printf("%s  K   K  %s   System:  %s %s %s\n", COLOR_RED, COLOR_RESET, COLOR_CYAN, sys_info.sysname, COLOR_RESET);
    printf("%s  K  K   %s   Node:    %s %s %s\n", COLOR_RED, COLOR_RESET, COLOR_CYAN, sys_info.nodename, COLOR_RESET);
    printf("%s  KKK    %s   Kernel:  %s %s %s\n", COLOR_RED, COLOR_RESET, COLOR_CYAN, sys_info.release, COLOR_RESET);
    printf("%s  K  K   %s   Shell:   %s k-shell v0.1 %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    printf("%s  K   K  %s   Author:  %s Kedrich %s\n", COLOR_RED, COLOR_RESET, COLOR_YELLOW, COLOR_RESET);
    printf("\n");
    return 1;
}

int k_shell_touch(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected filename\n");
        return 1;
    }

    FILE *f = fopen(args[1], "a");
    if (f == NULL) {
        perror("k-shell");
    } else {
        fclose(f);
    }
    return 1;
}

int k_shell_rm(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "k-shell: expected filename\n");
        return 1;
    }

    if (unlink(args[1]) != 0) {
        perror("k-shell");
    } else {
        printf("Deleted %s\n", args[1]);
    }
    return 1;
}

int k_shell_calc(char **args) {
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        fprintf(stderr, "usage: calc <num1> <op> <num2>\n");
        return 1;
    }

    double n1 = atof(args[1]);
    double n2 = atof(args[3]);
    char op = args[2][0]; 
    double result = 0;

    switch (op) {
        case '+': result = n1 + n2; break;
        case '-': result = n1 - n2; break;
        case '*': 
        case 'x': result = n1 * n2; break;
        case '/': 
            if (n2 == 0) {
                fprintf(stderr, "k-shell: cannot divide by zero\n");
                return 1;
            }
            result = n1 / n2; 
            break;
        default:
            fprintf(stderr, "k-shell: unknown operator '%c'\n", op);
            return 1;
    }

    printf("%sResult:%s %.2f\n", COLOR_GREEN, COLOR_RESET, result);
    return 1;
}