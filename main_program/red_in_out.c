/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:14:13 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 00:14:13 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirections(t_exex *exec, int start, int end)
{
    int i = start;
    int fd;

    while (i < end && exec->tokens[i].token)
    {
        if (exec->tokens[i].flag == TOKEN_REDIRECT_OUT && i + 1 < end && exec->tokens[i + 1].flag == TOKEN_FILENAME)
        {
            fd = open(exec->tokens[i + 1].token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(exec->tokens[i + 1].token);
                return (-1);
            }
            dup2(fd, 1);
            close(fd);
            i += 2;
        }
        else if (exec->tokens[i].flag == TOKEN_REDIRECT_IN && i + 1 < end && exec->tokens[i + 1].flag == TOKEN_FILENAME)
        {
            fd = open(exec->tokens[i + 1].token, O_RDONLY);
            if (fd < 0)
            {
                perror(exec->tokens[i + 1].token);
                return (-1);
            }
            dup2(fd, 0);
            close(fd);
            i += 2;
        }
        else if (exec->tokens[i].flag == TOKEN_APPEND && i + 1 < end && exec->tokens[i + 1].flag == TOKEN_FILENAME)
        {
            fd = open(exec->tokens[i + 1].token, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(exec->tokens[i + 1].token);
                return (-1);
            }
            dup2(fd, 1);
            close(fd);
            i += 2;
        }
        else
            i++;
    }
    return (0);
}