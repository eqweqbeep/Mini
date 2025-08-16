/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 05:46:20 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/11 05:46:20 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     is_valid_number(char *str)
{
    int     i;

    i = 0;
    if (!str || !*str)
        return (0);
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int     ft_exit(char **args)
{
    int     code;

    write(1, "exit\n", 5);
    if (!args[1])
        exit(0);
    if (!is_valid_number(args[1]))
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

