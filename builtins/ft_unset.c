/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by ChatGPT          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by ChatGPT         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <ctype.h>
#include <string.h>
extern char **environ;

static int valid(char *s)
{
        int i;

        if (!s || (!isalpha((unsigned char)s[0]) && s[0] != '_'))
                return (0);
        i = 1;
        while (s[i])
        {
                if (!isalnum((unsigned char)s[i]) && s[i] != '_')
                        return (0);
                i++;
        }
        return (1);
}

int ft_unset(char **a, char ***e)
{
        int i = 1, st = 0;

        while (a[i])
        {
                if (!valid(a[i]))
                        (write(2, "minishell: unset: `", 19),
                        write(2, a[i], strlen(a[i])),
                        write(2, "': not a valid identifier\n", 26), st = 1);
                else
                        unsetenv(a[i]);
                i++;
        }
        *e = environ;
        static_info()->env = arr_list(*e);
        return (st);
}
