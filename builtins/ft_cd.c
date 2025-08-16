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
extern char **environ;

int ft_cd(char **a, char ***e)
{
        char cwd[1024]; char *p = a[1]; char *old = getenv("PWD");

        if (a[1] && a[2])
                return (write(2, "minishell: cd: too many arguments\n", 34), 1);
        if (!p || !strcmp(p, "~"))
                p = getenv("HOME");
        else if (!strcmp(p, "-"))
        {
                if (!(p = getenv("OLDPWD")))
                        return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
                write(1, p, strlen(p)); write(1, "\n", 1);
        }
        if (!p)
                return (write(2, "minishell: cd: HOME not set\n", 28), 1);
        if (chdir(p))
        { write(2, "minishell: cd: ", 15); perror(p); return (1); }
        if (!getcwd(cwd, sizeof(cwd)))
                return (perror("cd"), 1);
        if (old) setenv("OLDPWD", old, 1);
        setenv("PWD", cwd, 1);
        *e = environ; static_info()->env = arr_list(*e);
}
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
