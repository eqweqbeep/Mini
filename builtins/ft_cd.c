/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:08 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:57:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../main_program/minishell.h"

static char *get_home(char **env)
{
        return (get_env_value(env, "HOME"));
}

int     ft_cd(char **args, char ***env)
{
        char    *path;
        char    oldpwd[1024];
        char    newpwd[1024];

        if (args[1] && args[2])
        {
                write(2, "minishell: cd: too many arguments\n", 34);
                return (1);
        }
        if (!args[1])
        {
                path = get_home(*env);
                if (!path)
                {
                        write(2, "minishell: cd: HOME not set\n", 28);
                        return (1);
                }
        }
        else
                path = args[1];
        if (!getcwd(oldpwd, sizeof(oldpwd)))
                oldpwd[0] = '\0';
        if (chdir(path) != 0)
        {
                write(2, "minishell: cd: ", 16);
                perror(path);
                return (1);
        }
        if (getcwd(newpwd, sizeof(newpwd)))
        {
                set_env_var(env, "OLDPWD", oldpwd);
                set_env_var(env, "PWD", newpwd);
        }
        return (0);
}
