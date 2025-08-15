/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/13 21:46:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     ft_pwd(char **args)
{
        char    cwd[1024];

        if (args[1])
        {
                write(2, "minishell: pwd: too many arguments\n", 35);
                return (1);
        }
        if (getcwd(cwd, sizeof(cwd)))
        {
                write(1, cwd, strlen(cwd));
                write(1, "\n", 1);
                return (0);
        }
        perror("pwd");
        return (1);
}
