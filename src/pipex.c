/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:14:32 by almejia-          #+#    #+#             */
/*   Updated: 2024/11/27 15:35:39 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

pid_t process_creator(char *cmd, char **env, int vars[], int pipefd[])  
{
	static int		iter = 0;
	pid_t			unity;
	int 			temp;
	
	unity = fork();
	if (unity < 0)
			error_exit("Fork failed");
	if (unity == 0)
	{ 
		dup2(vars[0], 0);
		dup2(vars[1], 1);
		(close(pipefd[0]), close(pipefd[1]), close(vars[iter]));
		temp = execute_command(cmd, env);
		if (temp == 1)
			error_exit("Error: Command not found");
		exit(0);
	}
	iter++;
	return (unity);
}

int	main(int argc, char **argv, char **env)
{
	static int	c = -1;
	int			pipefd[2];
	int			vars[2];
	int			stats;
	pid_t		unity[2];

	if (argc < 5)
		return (ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2), 1);
	if (pipe(pipefd) == -1)
		error_exit("Error: Pipe");
	while (++c != 2)
	{
		var_packer(argv, pipefd, vars, c);
		unity[c] = process_creator(argv[c + 2], env, vars, pipefd);
		close(vars[c]);
	}
	(close(pipefd[0]), close(pipefd[1]));
	(waitpid(unity[0], &stats, 0), waitpid(unity[1], &stats, 0));
	exit(WEXITSTATUS(stats));
	return (0);
}
