#ifndef SHELL_H
#define SHELL_H

void k_shell_print_prompt(void);
int k_shell_cd(char **args);
int k_shell_help(char **args);
int k_shell_exit(char **args);
int k_shell_clear(char **args);
int k_shell_env(char **args);
int k_shell_pwd(char **args);
int k_shell_echo(char **args);
int k_shell_whoami(char **args);
int k_shell_type(char **args);

#endif