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

// size_t ft_strlen(const char *s) {
//     size_t i = 0;
//     while (s[i])
//         i++;
//     return i;
// }

char *ft_substr(char const *s, unsigned int start, size_t len) {
    size_t i = 0;
    char *str;
    size_t s_len = ft_strlen(s);

    if (!s)
        return 0;
    if (start >= s_len)
        return ft_strdup("");
    if (len < s_len - start)
        str = malloc(len + 1);
    else
        str = malloc(s_len - start + 1);
    if (!str)
        return 0;
    while (i < len && s[start])
        str[i++] = s[start++];
    str[i] = 0;
    return str;
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
    size_t i = 0;
    if (n == 0)
        return 0;
    while ((i < n) && (s1[i] || s2[i])) {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return 0;
}

char *ft_strdup(const char *s) {
    size_t i = 0;
    char *cpy = malloc(ft_strlen(s) + 1);
    if (!cpy)
        return NULL;
    while (s[i]) {
        cpy[i] = s[i];
        i++;
    }
    cpy[i] = 0;
    return cpy;
}

void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
    {
        write(fd, s, 1);
        s++;
    }
}

void ft_putendl_fd(char *s, int fd)
{
    if (!s)
        return;
    ft_putstr_fd(s, fd);
    write(fd, "\n", 1);
}
