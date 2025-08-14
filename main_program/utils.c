/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:14:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:44:50 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strdup(const char *s)
{
    size_t  i;
    char    *cpy;

    i = 0;
    cpy = ft_malloc(ft_strlen((char *)s) + 1);
    while (s[i])
    {
        cpy[i] = s[i];
        i++;
    }
    cpy[i] = '\0';
    return (cpy);
}

void    ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return ;
    while (*s)
    {
        write(fd, s, 1);
        s++;
    }
}

void    ft_putendl_fd(char *s, int fd)
{
    if (!s)
        return ;
    ft_putstr_fd(s, fd);
    write(fd, "\n", 1);
}
