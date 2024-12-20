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

void	free_v2(char **trash)
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
			return (free_v2(paths), path);
		free(path);
		i++;
	}
	return (free_v2 (paths), NULL);
}

int	execute_command(char *cmd, char **env)
{
	char	**cmd_v;
	char	*path;

	cmd_v = ft_split(cmd, ' ');
	if ((access(cmd_v[0], F_OK | X_OK) == 0) \
		&& ft_strnstr(cmd_v[0], "./", 2))
	{
		if (execve(cmd_v[0], cmd_v, env) == -1)
			return (free_v2(cmd_v), 1);
	}
	else if (access(cmd_v[0], F_OK | X_OK) != 0 && ft_strchr(cmd_v[0], '/'))
		return (free_v2(cmd_v), 1);
	else
	{
		path = find_path(cmd_v[0], env);
		if (path == NULL || execve(path, cmd_v, env) == -1)
			return (free_v2(cmd_v), 1);
		free(path);
	}
	return (0);
}
