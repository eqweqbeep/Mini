/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:08 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by ChatGPT         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_cd(char **args)
{
        char *path;

        if (args[1] && args[2])
                return (write(2, "minishell: cd: too many arguments\n", 34), 1);
        path = args[1] ? args[1] : getenv("HOME");
        if (!path)
                return (write(2, "minishell: cd: HOME not set\n", 28), 1);
        if (chdir(path))
        {
                write(2, "minishell: cd: ", 15);
                perror(path);
                return (1);
        }
        return (0);
}
