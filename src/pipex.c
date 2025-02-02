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

#include "../include/pipex.h"

char	**parse(t_node **lst, char *cmd)
{
	int	iter;
	int	t_len;
	int	in_single_quote;
	
	iter = 0;
	t_len = 0;
	in_single_quote = 0;
	while (cmd[iter])
	{
		if (cmd[iter] == '\'')
			in_single_quote = !in_single_quote;
		else if ((cmd[iter + 1] == '\0')
			|| (cmd[iter] == ' ' && !in_single_quote))
		{
			if (t_len > 0)
			{
				ft_update_list(lst, ft_substr(cmd, iter, t_len));
				t_len = 0;
			}
		}
		else
			t_len++;
		iter++;
	}
	return (ft_make_arr(*lst));
}

int	ft_execute_command(char *cmd, char **env)
{
	t_node		*lst;
	char		**cmd_v;
	char		*path;
	static int	exit_status = 0;

	
	if (!cmd || !*cmd)
		return (1);
	lst = NULL;
	cmd_v = parse(&lst, cmd);
	if (access(cmd_v[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd_v[0], cmd_v, env) == -1)
			exit_status = 1;
	}
	else
	{
		path = ft_find_path(cmd_v[0], env);
		if (path == NULL || execve(path, cmd_v, env) == -1)
			exit_status = 1;
	}
	if (path)
		free(path);
	(ft_free_arr(cmd_v), ft_free_lst_content(lst));
	return (exit_status);
}

pid_t	process_creator(char *cmd, char **env, int vars[], int pipefd[])
{
	static int		iter = 0;
	pid_t			unity;
	int				temp;
	
	unity = fork();
	if (unity < 0)
		ft_error_exit("Fork failed");
	if (unity == 0)
	{
		if (dup2(vars[0], 0) == -1)
		{
			ft_error_exit("fallo");
		}
		if (dup2(vars[1], 1) == -1)
		{
			ft_error_exit("fallo");
		}
		(close(pipefd[0]), close(pipefd[1]), close(vars[iter]));
		temp = ft_execute_command(cmd, env);
		if (temp == 1)
			ft_error_exit("Error: Command not found");
		exit(0);
	}
	iter++;
	return (unity);
}

int	var_packer(char **argv, int pipefd[], int vars[], int flag)
{
	if (flag == 0)
	{
		vars[0] = open(argv[1], O_RDONLY, 0644);
		if (vars[0] < 0)
			return (perror("bash: infile"), 0);
		vars[1] = pipefd[1];
	}
	if (flag == 1)
	{
		vars[0] = pipefd[0];
		vars[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (vars[1] < 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	static int	c = 0;
	int			pipefd[2];
	int			vars[2];
	int			stats;
	pid_t		unity[2];

	if (argc < 5)
		return (ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2), 1);
	if (pipe(pipefd) == -1)
		ft_error_exit("Error: Pipe");
	while (c != 2)
	{
		if (var_packer(argv, pipefd, vars, c))
			unity[c] = process_creator(argv[c + 2], env, vars, pipefd);
		close(vars[c]);
		c++;
	}
	(close(pipefd[0]), close(pipefd[1]));
	(waitpid(unity[0], &stats, 0), waitpid(unity[1], &stats, 0));
	exit(WEXITSTATUS(stats));
	return (0);
}
