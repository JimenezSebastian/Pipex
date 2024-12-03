/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:56:01 by almejia-          #+#    #+#             */
/*   Updated: 2024/10/21 19:44:30 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void frees(char **trash)
{
	int		i;

	i = 0;
	while (trash[i])
		free(trash[i++]);
	free(trash);
}

void	error_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

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
			return (frees(paths), path);
		free(path);
		i++;
	}
	return (frees (paths), NULL);
}

int 	execute_command(char *cmd, char **env)
{
	char	**cmd_v;
	char	*path;

	cmd_v = ft_split(cmd, ' ');
	if ((access(cmd_v[0], F_OK | X_OK) == 0) \
		&& ft_strnstr(cmd_v[0], "./", 2))
	{	
		if (execve(cmd_v[0], cmd_v, env) == -1)
				return (frees(cmd_v), 1);
	}
	else if (access(cmd_v[0], F_OK | X_OK) != 0 && ft_strchr(cmd_v[0], '/'))
			return (frees(cmd_v), 1);
	else
	{
		path = find_path(cmd_v[0], env);
		if (path == NULL || execve(path, cmd_v, env) == -1)
				return (frees(cmd_v), 1);
		free(path);
	}
	return (0);
}

void var_packer(char **argv, int pipefd[], int vars[], int flag)
{
	if (flag == 0)
	{
		vars[0] = open(argv[1], O_RDONLY, 0777);
		vars[1] = pipefd[1];
		if (vars[0] < 0)
			error_exit("Error: Infile");
 	}
	if (flag == 1)
	{
		vars[0] = pipefd[0];
		vars[1] = open(argv[4], O_WRONLY, O_APPEND, O_CREAT | 0777);
		if (vars[1] < 0)
			error_exit("Error: Outfile");
	}
}
