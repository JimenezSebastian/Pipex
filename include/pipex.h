/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 06:01:45 by almejia-          #+#    #+#             */
/*   Updated: 2024/12/19 06:01:47 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <aio.h>

typedef struct t_node
{
	char			*token;
	struct t_node	*next;
}	t_node;

// Pipex Utils.
int		ft_execute_command(char *cmd, char **env);
char	*ft_find_path(char *cmd, char **env);
void	ft_error_exit(char *error_msg);
void	ft_free_arr(char **trash);
void	ft_free_lst_content(t_node *lst);

// Lst Utils.
void	ft_update_list(t_node **lst, char *token);
char	**ft_make_arr(t_node *lst);
t_node	*ft_node_maker(char *token);
int		ft_add_nodes(t_node **lst, t_node *new_node);
int		ft_lstlen(t_node *lst);

#endif
