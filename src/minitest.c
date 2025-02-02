#include "../include/pipex.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*copy;
	char	*ptr;

	len = ft_strlen(s1) + 1;
	copy = malloc(len);
	ptr = copy;
	if (!copy)
		return (0);
	while (*s1)
		*(copy++) = *(s1++);
	*copy = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c] != '\0')
	{
		++c;
	}
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc((len + 1));
	if (!sub)
		return (0);
	while (len > i)
		sub[i++] = *(s++ + start);
	sub[i] = '\0';
	return (sub);
}

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

int main(int argc, char **argv)
{
    t_node *head = NULL;
	char *str = argv[1];
    char **matrix;
    int i = 0;

	if (argc != 2)
		return(write(1, "lol", 3));
    matrix = parse(&head, str);
    while (head)
    {
        printf("t_lst%s", head->token);
        head = head->next;   
    }
    while (matrix[i])
    {
        printf("t_matrx%s", matrix[i]);
        i++;
    }
    return(0);
}