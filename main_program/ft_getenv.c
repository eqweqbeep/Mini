/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:57:12 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/13 06:43:19 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     *get_env(t_env *env, char *s)
{
        size_t  key_len;
        t_env   *current;

        key_len = 0;
        current = env;
        while (s[key_len] && s[key_len] != '=')
                key_len++;
        while (current)
        {
                if (ft_strncmp(current->s, s, key_len) == 0
                        && current->s[key_len] == '=')
                        return (ft_substr(current->s + key_len + 1,
                                        ft_strlen(current->s) - (key_len + 1)));
                current = current->next;
        }
        return (ft_substr("", 1));
}

static char     *itoa(int n)
{
        int     len;
        int     tmp;
        char    *s;

        len = 1;
        tmp = n;
        while (tmp > 9)
        {
                tmp /= 10;
                len++;
        }
        s = malloc(len + 1);
        if (!s)
                return (NULL);
        s[len] = '\0';
        if (n == 0)
                s[0] = '0';
        while (n > 0)
        {
                s[--len] = (n % 10) + '0';
                n /= 10;
        }
        return (s);
}

char    *ft_getenv(char *token, int *len)
{
        char    *s;
        char    *name;
        t_info  *info;

        info = static_info();
        if (token[1] == '?' && *len == 2)
        {
                s = itoa(info->exit_status);
                if (!s)
                        return (NULL);
                *len = ft_strlen(s);
                return (s);
        }
        name = ft_substr(token + 1, *len - 1);
        if (!name)
                return (NULL);
        s = get_env(info->env, name);
        *len = ft_strlen(s);
        return (s);
}

