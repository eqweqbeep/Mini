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

static int open_file(t_rediraction *r)
{
    if (r->type == TOKEN_REDIRECT_OUT)
        return (open(r->token, O_WRONLY | O_CREAT | O_TRUNC, 0644));
    if (r->type == TOKEN_APPEND)
        return (open(r->token, O_WRONLY | O_CREAT | O_APPEND, 0644));
    if (r->type == TOKEN_REDIRECT_IN)
        return (open(r->token, O_RDONLY));
    if (r->type == TOKEN_HEREDOC)
        return (r->fd);
    return (-2);
}

static int apply_redirection(t_rediraction *r, int fd)
{
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
    return (0);
}

int handle_redirections(t_list *exec)
{
    t_rediraction   *r;
    int             fd;

    r = exec->rediraction;
    while (r)
    {
        fd = open_file(r);
        if (fd == -2)
        {
            r = r->next;
            continue ;
        }
        if (apply_redirection(r, fd) == -1)
            return (-1);
        r = r->next;
    }
    return (0);
}
