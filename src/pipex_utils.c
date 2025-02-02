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

#include "../include/pipex.h"

char	*ft_find_path(char *cmd, char **env)
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
			return (ft_free_arr(paths), path);
		free(path);
		i++;
	}
	return (ft_free_arr (paths), NULL);
}

void	ft_free_arr(char **trash)
{
	int		i;

	i = 0;
	while (trash[i])
		free(trash[i++]);
	free(trash);
}

void	ft_free_lst_content(t_node *lst)
{
	t_node	*delete;

	if (!lst)
		return ;
	while (lst)
	{
		free(lst->token);
		delete = lst;
		lst = lst->next;
		free(delete);
	}
}

void	ft_error_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}
