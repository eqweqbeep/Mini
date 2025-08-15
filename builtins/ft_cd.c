/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:08 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/13 21:54:53 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>

int     ft_cd(char **args)
{
        if (args[1] && args[2])
        {
                write(2, "minishell: cd: too many arguments\n", 34);
                return (1);
        }
        if (!args[1])
        {
                write(2, "minishell: cd: HOME not set\n", 27);
                return (1);
        }
        if (chdir(args[1]) != 0)
        {
                write(2, "minishell: cd: ", 16);
                write(2, args[1], strlen(args[1]));
                write(2, ": ", 2);
                write(2, strerror(errno), strlen(strerror(errno)));
                write(2, "\n", 1);
                return (1);
        }
        return (0);
}
