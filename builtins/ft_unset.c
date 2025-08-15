/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
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
        while (s[i])
        {
                if (!isalnum(s[i]) && s[i] != '_')
                        return (0);
                i++;
        }
        return (1);
}

int     ft_unset(char **args, char ***env)
{
        int     i;
        int     status;

        i = 1;
        status = 0;
        while (args[i])
        {
                if (!valid_identifier(args[i]))
                {
                        write(2, "minishell: unset: `", 20);
                        write(2, args[i], strlen(args[i]));
                        write(2, "': not a valid identifier\n", 26);
                        status = 1;
                }
                else
                        unset_env_var(env, args[i]);
                i++;
        }
        return (status);
}

