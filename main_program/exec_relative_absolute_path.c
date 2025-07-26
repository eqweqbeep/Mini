/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 00:13:27 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_absolute_path(t_exex *exec, char **env)
{
    if (!exec->cmd_with_flags[0])
        exit(0);
    if (exec->cmd_with_flags[0][0] == '/' || (exec->cmd_with_flags[0][0] == '.' && exec->cmd_with_flags[0][1] == '/'))
    {
        if (access(exec->cmd_with_flags[0], X_OK) == 0)
        {
            if (execve(exec->cmd_with_flags[0], exec->cmd_with_flags, env) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "%s: permission denied or not found\n", exec->cmd_with_flags[0]);
            exit(126);
        }
    }
}

void execute_relative_path(t_exex *exec, char **env)
{
    int i = 0;
    if (!exec->cmd_with_flags[0])
        exit(0);
    exec->paths = extract_paths(env, exec);
    if (!exec->paths)
    {
        fprintf(stderr, "%s: command not found\n", exec->cmd_with_flags[0]);
        exit(127);
    }
    while (exec->paths[i])
    {
        exec->path = join_by_order(exec->paths[i], '/', exec->cmd_with_flags[0]);
        if (exec->path && access(exec->path, X_OK | F_OK) == 0)
        {
            if (execve(exec->path, exec->cmd_with_flags, env) == -1)
            {
                perror("execve");
                free(exec->path);
                exit(1);
            }
        }
        free(exec->path);
        exec->path = NULL;
        i++;
    }
}