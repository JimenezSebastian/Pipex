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

/* void handle_here_doc(char **argv, char **env)
{
        char    *line;
        char    *limiter;
        int     pipefd[2];

        pipe(pipefd);
        limiter = ft_strjoin(argv[2], "\n");
        close (pipefd[0]);
        while (1)
        {
                ft_pustr_fd("heardoc> ", 1);
                line = get_next_line(0);
                if (ft_strcmp(line, limiter) == 0)
                        break;
                ft_pustr_fd(line, pipefd[1]);
                free (line);
        }
        close (pipefd[1]);
        free (line);
        free(limiter);
        exit(0);
        close(pipefd[1]);
        wait(NULL);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        pipex(argv + 3, env);
}


 */
