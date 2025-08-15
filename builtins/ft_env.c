/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/13 21:46:17 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     ft_env(char **args, char **env)
{
        int     i;

        if (args[1])
        {
                write(2, "minishell: env: too many arguments\n", 36);
                return (1);
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
