/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:31:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_absolute_path(t_list *exec, char **env)
{
    if (!exec->cmds[0])
        exit(0);
    if (exec->cmds[0][0] == '/' || (exec->cmds[0][0] == '.' && exec->cmds[0][1] == '/'))
    {
        if (access(exec->cmds[0], X_OK) == 0)
        {
            if (execve(exec->cmds[0], exec->cmds, env) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "%s: permission denied or not found\n", exec->cmds[0]);
            exit(126);
        }
    }
}

static void try_exec(t_list *exec, char **env, int i)
{
    exec->path = join_by_order(exec->paths[i], '/', exec->cmds[0]);
    if (exec->path && access(exec->path, X_OK | F_OK) == 0)
    {
        if (execve(exec->path, exec->cmds, env) == -1)
        {
            perror("execve");
            free(exec->path);
            exit(1);
        }
    }
    free(exec->path);
    exec->path = NULL;
}

void execute_relative_path(t_list *exec, char **env)
{
    int i;

    if (!exec->cmds[0])
        exit(0);
    exec->paths = extract_paths(env, exec);
    if (!exec->paths)
    {
        fprintf(stderr, "%s: command not found\n", exec->cmds[0]);
        exit(127);
    }
    i = 0;
    while (exec->paths[i])
    {
        try_exec(exec, env, i);
        i++;
    }
}