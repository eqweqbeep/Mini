/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/30 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../main_program/minishell.h"

static char *ms_strdup(const char *s)
{
        size_t  len;
        char    *dup;

        len = strlen(s);
        dup = malloc(len + 1);
        if (!dup)
                return (NULL);
        memcpy(dup, s, len);
        dup[len] = '\0';
        return (dup);
}

static char *ms_strjoin(const char *s1, const char *s2)
{
        size_t  len1;
        size_t  len2;
        char    *res;

        len1 = strlen(s1);
        len2 = strlen(s2);
        res = malloc(len1 + len2 + 1);
        if (!res)
                return (NULL);
        memcpy(res, s1, len1);
        memcpy(res + len1, s2, len2);
        res[len1 + len2] = '\0';
        return (res);
}

static int  is_valid_identifier(const char *s)
{
        int i;

        if (!s || !s[0] || (!((s[0] >= 'a' && s[0] <= 'z') ||
                                (s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_')))
                return (0);
        i = 1;
        while (s[i] && s[i] != '=')
        {
                if (!((s[i] >= 'a' && s[i] <= 'z') ||
                                (s[i] >= 'A' && s[i] <= 'Z') ||
                                (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
                        return (0);
                i++;
        }
        return (1);
}

static int  get_index(char **env, char *arg)
{
        int len;
        int i;

        len = 0;
        while (arg[len] && arg[len] != '=')
                len++;
        i = 0;
        while (env && env[i])
        {
                if (!strncmp(env[i], arg, len) && env[i][len] == '=')
                        return (i);
                i++;
        }
        return (-1);
}

static void set_env_array(char *arg, char ***envp)
{
        char    **env;
        char    **new_env;
        int     count;
        int     i;
        int     idx;

        env = *envp;
        idx = get_index(env, arg);
        if (idx >= 0)
        {
                free(env[idx]);
                env[idx] = ms_strdup(arg);
                return ;
        }
        count = 0;
        while (env && env[count])
                count++;
        new_env = malloc(sizeof(char *) * (count + 2));
        if (!new_env)
                return ;
        i = 0;
        while (i < count)
        {
                new_env[i] = env[i];
                i++;
        }
        new_env[count] = ms_strdup(arg);
        new_env[count + 1] = NULL;
        *envp = new_env;
}

static void set_env_list(char *arg, t_env **env)
{
        t_env   *curr;
        int     len;

        curr = *env;
        len = 0;
        while (arg[len] && arg[len] != '=')
                len++;
        while (curr)
        {
                if (!strncmp(curr->s, arg, len) && curr->s[len] == '=')
                {
                        ft_free(curr->s);
                        curr->s = ft_strdup(arg);
                        return ;
                }
                if (!curr->next)
                        break ;
                curr = curr->next;
        }
        curr = malloc(sizeof(t_env));
        if (!curr)
                return ;
        curr->s = ft_strdup(arg);
        curr->next = NULL;
        if (!*env)
                *env = curr;
        else
        {
                t_env *tmp = *env;
                while (tmp->next)
                        tmp = tmp->next;
                tmp->next = curr;
        }
}

static void print_export_env(t_env *env)
{
        while (env)
        {
                ft_putstr_fd("declare -x ", 1);
                ft_putendl_fd(env->s, 1);
                env = env->next;
        }
}

int     ft_export(char **args, char ***envp)
{
        int     i;
        int     status;
        char    *tmp;
        t_info  *info;

        info = static_info();
        if (!args[1])
        {
                print_export_env(info->env);
                return (0);
        }
        i = 1;
        status = 0;
        while (args[i])
        {
                if (!is_valid_identifier(args[i]))
                {
                        ft_putstr_fd("minishell: export: `", 2);
                        ft_putstr_fd(args[i], 2);
                        ft_putendl_fd("': not a valid identifier", 2);
                        status = 1;
                }
                else
                {
                        if (!strchr(args[i], '='))
                                tmp = ms_strjoin(args[i], "=");
                        else
                                tmp = ms_strdup(args[i]);
                        if (tmp)
                        {
                                set_env_array(tmp, envp);
                                set_env_list(tmp, &info->env);
                                free(tmp);
                        }
                        else
                                status = 1;
                }
                i++;
        }
        return (status);
}
