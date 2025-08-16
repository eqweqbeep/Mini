/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 05:46:20 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by ChatGPT         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <ctype.h>

static int numeric(char *s)
{
        int i;

        if (!s || !*s)
                return (0);
        i = 0;
        if (s[i] == '+' || s[i] == '-')
                i++;
        while (s[i])
                if (!isdigit((unsigned char)s[i++]))
                        return (0);
        return (1);
}

int ft_exit(char **args)
{
        int code;

        write(1, "exit\n", 5);
        if (!args[1])
                exit(0);
        if (!numeric(args[1]))
        {
                write(2, "minishell: exit: ", 17);
                write(2, args[1], strlen(args[1]));
                write(2, ": numeric argument required\n", 28);
                exit(2);
        }
        if (args[2])
        {
                write(2, "minishell: exit: too many arguments\n", 36);
                return (1);
        }
        code = atoi(args[1]);
        exit(code);
}
