#ifndef PIPEX_H
# define PIPEX_H

#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <aio.h>
#include <stdio.h>

pid_t   process_creator(char *cmd, char **env, int vars[], int pipefd[]);
void    var_packer(char **argv, int pipefd[], int vars[], int flag);
int    	execute_command (char *cmd, char  **env);
char	*find_path(char *cmd, char **env);
void	error_exit(char *error_msg);
void	frees(char **trash);
int     main(int argc, char **argv, char **env);

#endif
