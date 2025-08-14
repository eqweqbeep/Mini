/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirections(t_list *exec)
{
    t_rediraction   *r;
    int             fd;

    r = exec->rediraction;
    while (r)
    {
        if (r->type == TOKEN_REDIRECT_OUT)
            fd = open(r->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (r->type == TOKEN_APPEND)
            fd = open(r->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (r->type == TOKEN_REDIRECT_IN)
            fd = open(r->token, O_RDONLY);
        else if (r->type == TOKEN_HEREDOC)
            fd = r->fd;
        else
        {
            r = r->next;
            continue;
        }
        if (fd < 0)
        {
            perror(r->token);
            return (-1);
        }
        if (r->type == TOKEN_REDIRECT_IN || r->type == TOKEN_HEREDOC)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        r = r->next;
    }
    return (0);
}
