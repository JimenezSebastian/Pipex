#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <aio.h>
#include "libft.h"
#include <error.h>
#include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
void error_exit(char *error_msg)
{
    perror(error_msg);
    exit(1);
}

char  *find_path(char *cmd, char **env)
{
	char 	**paths;
	char 	*path;
	char 	*temp;
	int 	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] +5, ':');
	i = 0;
	while (paths[i])
	{ 
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free (temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (cmd);
}

void execute_command (char *cmd, char  **env)
{
	char **cmd_v;
	char *path;

	cmd_v = ft_split(cmd, ' ');
	path = find_path(cmd_v[0], env);
	if (path == NULL)
		error_exit("Command not found");
	if (execve(path, cmd_v, env) == -1)
		error_exit("execve failed");
}

void	pipex(char **argv, char **env)
{
	int fd_in;
        int fd_out;
        int pipefd[2];
	int status;
        pid_t pid1;
        pid_t pid2;
	
	fd_in = open(argv[1], O_RDONLY, 0777);
     	if (fd_in < 0)
                error_exit("Error: Infile");
        fd_out = open (argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (fd_out < 0)
                error_exit("Error: Outfile");
        if (pipe(pipefd) == -1)
                error_exit("Error: Pipe");
        pid1 = fork();
        if (pid1 < 0)
                error_exit("Fork1 failed");
        else if (pid1 == 0)
        {
                dup2(fd_in, 0);
                dup2(pipefd[1], 1);
                close(pipefd[0]);
                close(pipefd[1]);
                close(fd_in);
                close(fd_out);
                execute_command(argv[2], env);
                exit(0);
        }
        pid2 = fork();
        if (pid2 < 0)
                error_exit("Fork2 failed");
        else if (pid2 == 0)
        {
                dup2(pipefd[0], 0);
                dup2(fd_out, 1);
                (close(pipefd[0]), close(pipefd[1]), close(fd_in), close(fd_out));
                execute_command(argv[3], env);
                exit(0);
        }
        close(pipefd[0]);
        close(pipefd[1]);
        close(fd_in);
        close(fd_out);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}

int main(int argc, char **argv, char **env)
{
	if (argc < 5)
		return (ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2), 1);
	pipex(argv, env);
	return (0);
}
