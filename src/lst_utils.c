/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:34:46 by almejia-          #+#    #+#             */
/*   Updated: 2025/01/28 15:34:48 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_update_list(t_node **lst, char *token)
{
	t_node	*node;

	node = ft_node_maker(token);
	ft_add_nodes(lst, node);
}

char	**ft_make_arr(t_node *lst)
{
	char	**tokens;
	int		n;

	n = ft_lstlen(lst) + 1;
	tokens = malloc(n * sizeof(char *));
	n = 0;
	while (lst)
	{
		tokens[n] = lst->token;
		lst = lst->next;
		n++;
	}
	tokens[n] = NULL;
	return (tokens);
}

t_node	*ft_node_maker(char *token)
{
	t_node	*ptr;

	ptr = malloc(1 * sizeof(t_node));
	if (!ptr)
		return (NULL);
	ptr->token = token;
	ptr->next = NULL;
	return (ptr);
}

int	ft_add_nodes(t_node **lst, t_node *new_node)
{
	t_node	*ptr;

	ptr = *lst;
	if (!new_node)
		return (1);
	if (!ptr)
		ptr = new_node;
	else
	{
		while (ptr)
			ptr = ptr->next;
		ptr->next = new_node;
	}
	return (0);
}

int	ft_lstlen(t_node *lst)
{
	int	c;

	c = 0;
	while (lst)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}
