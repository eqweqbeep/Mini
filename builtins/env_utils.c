#include "builtins.h"
#include "../main_program/minishell.h"

static int  find_env_index(char **env, const char *name)
{
        size_t  len;
        int     i;

        if (!env || !name)
                return (-1);
        len = strlen(name);
        i = 0;
        while (env[i])
        {
                if (!strncmp(env[i], name, len) && env[i][len] == '=')
                        return (i);
                i++;
        }
        return (-1);
}

char    *get_env_value(char **env, const char *name)
{
        int     idx;
        char    *eq;

        idx = find_env_index(env, name);
        if (idx == -1)
                return (NULL);
        eq = strchr(env[idx], '=');
        if (!eq)
                return (NULL);
        return (eq + 1);
}

int     set_env_var(char ***env, const char *name, const char *value)
{
        size_t  len_name;
        size_t  len_value;
        char    *entry;
        int     idx;
        char    **new_env;
        t_info  *info;
        t_env   *cur;
        t_env   *prev;
        t_env   *node;

        if (!env || !name)
                return (1);
        len_name = strlen(name);
        len_value = value ? strlen(value) : 0;
        entry = malloc(len_name + 1 + len_value + 1);
        if (!entry)
                return (1);
        memcpy(entry, name, len_name);
        entry[len_name] = '=';
        if (value)
                memcpy(entry + len_name + 1, value, len_value);
        entry[len_name + 1 + len_value] = '\0';
        idx = find_env_index(*env, name);
        if (idx >= 0)
        {
                free((*env)[idx]);
                (*env)[idx] = entry;
        }
        else
        {
                idx = 0;
                while ((*env)[idx])
                        idx++;
                new_env = realloc(*env, sizeof(char *) * (idx + 2));
                if (!new_env)
                        return (free(entry), 1);
                new_env[idx] = entry;
                new_env[idx + 1] = NULL;
                *env = new_env;
        }
        info = static_info();
        cur = info->env;
        prev = NULL;
        while (cur)
        {
                if (!strncmp(cur->s, name, len_name) && cur->s[len_name] == '=')
                {
                        entry = strdup(entry);
                        if (!entry)
                                return (1);
                        free(cur->s);
                        cur->s = entry;
                        return (0);
                }
                prev = cur;
                cur = cur->next;
        }
        node = malloc(sizeof(t_env));
        if (!node)
                return (1);
        node->s = strdup(entry);
        if (!node->s)
                return (free(node), 1);
        node->next = NULL;
        if (!prev)
                info->env = node;
        else
                prev->next = node;
        return (0);
}

int     unset_env_var(char ***env, const char *name)
{
        size_t  len_name;
        int     i;
        int     j;
        t_info  *info;
        t_env   *cur;
        t_env   *prev;

        if (!env || !*env || !name)
                return (1);
        len_name = strlen(name);
        i = 0;
        j = 0;
        while ((*env)[i])
        {
                if (!strncmp((*env)[i], name, len_name) && (*env)[i][len_name] == '=')
                {
                        free((*env)[i]);
                        i++;
                        continue ;
                }
                (*env)[j++] = (*env)[i++];
        }
        (*env)[j] = NULL;
        info = static_info();
        cur = info->env;
        prev = NULL;
        while (cur)
        {
                if (!strncmp(cur->s, name, len_name) && cur->s[len_name] == '=')
                {
                        if (prev)
                                prev->next = cur->next;
                        else
                                info->env = cur->next;
                        free(cur->s);
                        free(cur);
                        break ;
                }
                prev = cur;
                cur = cur->next;
        }
        return (0);
}
