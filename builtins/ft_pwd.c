/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:57:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     ft_pwd(char **args)
{
        char    cwd[1024];

        (void)args;
        if (!getcwd(cwd, sizeof(cwd)))
        {
                perror("minishell: pwd");
                return (1);
        }
        write(1, cwd, strlen(cwd));
        write(1, "\n", 1);
        return (0);
}

