/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc(char *delimiter)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
        return (-1);
    while (1)
    {
        line = readline("heredoc>$");
        if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
        {
            free(line);
            break ;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return (fd[0]);
}

void    prepare_heredocs(t_list *exec)
{
    t_rediraction   *r;

    while (exec)
    {
        r = exec->rediraction;
        while (r)
        {
            if (r->type == TOKEN_HEREDOC)
                r->fd = heredoc(r->token);
            r = r->next;
        }
        exec = exec->next;
    }
}

