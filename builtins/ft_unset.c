/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/30 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../main_program/minishell.h"

static int  is_valid_identifier(const char *s)
{
        int i;

        if (!s || !s[0] || (!((s[0] >= 'a' && s[0] <= 'z') ||
                                (s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_')))
                return (0);
        i = 1;
        while (s[i])
        {
                if (!((s[i] >= 'a' && s[i] <= 'z') ||
                                (s[i] >= 'A' && s[i] <= 'Z') ||
                                (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
                        return (0);
                i++;
        }
        return (1);
}

static void remove_from_env_array(char *name, char ***envp)
{
        int     len;
        int     i;
        int     j;
        char    **env;

        env = *envp;
        len = strlen(name);
        i = 0;
        while (env && env[i])
        {
                if (!strncmp(env[i], name, len) && env[i][len] == '=')
                {
                        free(env[i]);
                        j = i;
                        while (env[j])
                        {
                                env[j] = env[j + 1];
                                j++;
                        }
                        break ;
                }
                i++;
        }
}

static void remove_from_env_list(char *name, t_env **env)
{
        t_env   *curr;
        t_env   *prev;
        int     len;

        curr = *env;
        prev = NULL;
        len = strlen(name);
        while (curr)
        {
                if (!strncmp(curr->s, name, len) && curr->s[len] == '=')
                {
                        if (prev)
                                prev->next = curr->next;
                        else
                                *env = curr->next;
                        ft_free(curr->s);
                        free(curr);
                        return ;
                }
                prev = curr;
                curr = curr->next;
        }
}

int     ft_unset(char **args, char ***envp)
{
        int     i;
        int     status;
        t_info  *info;

        info = static_info();
        i = 1;
        status = 0;
        while (args[i])
        {
                if (!is_valid_identifier(args[i]))
                {
                        ft_putstr_fd("minishell: unset: `", 2);
                        ft_putstr_fd(args[i], 2);
                        ft_putendl_fd("': not a valid identifier", 2);
                        status = 1;
                }
                else
                {
                        remove_from_env_array(args[i], envp);
                        remove_from_env_list(args[i], &info->env);
                }
                i++;
        }
        return (status);
}
