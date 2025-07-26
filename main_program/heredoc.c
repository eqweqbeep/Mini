/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/26 09:28:32 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void heredoc_process(char *delimiter)
{
    char *r_line;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    signal(SIGINT, SIG_DFL); 
    while (1)
    {
        r_line = readline("\033[95mheredoc >$\033[0m");
        if (!r_line)
        {
            write(2, "warning: heredoc delimited by end-of-file\n", 42);
            break;
        }
        if (strcmp(r_line, delimiter) == 0)
        {
            free(r_line);
            break;
        }
        write(fd[1], r_line, strlen(r_line));
        write(fd[1], "\n", 1);
        free(r_line);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
}

void heredoc(t_exex *exec, int start, int end)
{
    int i = start;
    char *delimiter = NULL;

    while (i < end && exec->tokens[i].token)
    {
        if (exec->tokens[i].flag == TOKEN_HEREDOC && i + 1 < end && exec->tokens[i + 1].flag == TOKEN_DELIMITER)
        {
            delimiter = ft_strdup(exec->tokens[i + 1].token);
            if (!delimiter)
                exit(1);
            heredoc_process(delimiter);
            free(delimiter);
            i += 2;
        }
        else
            i++;
    }
}