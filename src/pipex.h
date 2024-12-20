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

# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <aio.h>
# include <stdio.h>
# include "libft.h"

pid_t	process_creator(char *cmd, char **env, int vars[], int pipefd[]);
int		var_packer(char **argv, int pipefd[], int vars[], int flag);
int		execute_command(char *cmd, char **env);
char	*find_path(char *cmd, char **env);
void	error_exit(char *error_msg);
void	free_v2(char **trash);
int		main(int argc, char **argv, char **env);

#endif
