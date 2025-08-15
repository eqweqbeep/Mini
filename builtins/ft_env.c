/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:57:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     ft_env(char **args, char **env)
{
        int     i;

        if (args[1])
        {
                write(2, "minishell: env: ", 16);
                write(2, args[1], strlen(args[1]));
                write(2, ": No such file or directory\n", 28);
                return (127);
        }
        i = 0;
        while (env[i])
        {
                write(1, env[i], strlen(env[i]));
                write(1, "\n", 1);
                i++;
        }
        return (0);
}

