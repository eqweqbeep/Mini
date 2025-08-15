/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 06:57:00 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:57:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../main_program/minishell.h"

static int      valid_identifier(const char *s)
{
        int     i;

        if (!s || (!isalpha(s[0]) && s[0] != '_'))
                return (0);
        i = 1;
        while (s[i] && s[i] != '=')
        {
                if (!isalnum(s[i]) && s[i] != '_')
                        return (0);
                i++;
        }
        return (1);
}

int     ft_export(char **args, char ***env)
{
        int     i;
        int     status;
        char    *name;
        char    *value;
        int     len;

        if (!args[1])
        {
                i = 0;
                while ((*env)[i])
                {
                        write(1, (*env)[i], strlen((*env)[i]));
                        write(1, "\n", 1);
                        i++;
                }
                return (0);
        }
        i = 1;
        status = 0;
        while (args[i])
        {
                if (!valid_identifier(args[i]))
                {
                        write(2, "minishell: export: `", 20);
                        write(2, args[i], strlen(args[i]));
                        write(2, "': not a valid identifier\n", 26);
                        status = 1;
                        i++;
                        continue ;
                }
                len = 0;
                while (args[i][len] && args[i][len] != '=')
                        len++;
                name = malloc(len + 1);
                if (!name)
                        return (1);
                memcpy(name, args[i], len);
                name[len] = '\0';
                value = NULL;
                if (args[i][len] == '=')
                        value = args[i] + len + 1;
                if (set_env_var(env, name, value))
                        status = 1;
                free(name);
                i++;
        }
        return (status);
}

