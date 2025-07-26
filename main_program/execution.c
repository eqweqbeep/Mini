/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 18:08:26 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "minishell.h"

void free_exec(t_exex *exec)
{
    int i;

    if (exec->cmd_with_flags)
    {
        for (i = 0; exec->cmd_with_flags[i]; i++)
            free(exec->cmd_with_flags[i]);
        free(exec->cmd_with_flags);
    }
    if (exec->paths)
    {
        for (i = 0; exec->paths[i]; i++)
            free(exec->paths[i]);
        free(exec->paths);
    }
    if (exec->path)
        free(exec->path);
    if (exec->pids)
        free(exec->pids);
    if (exec->pipe_fds)
        free(exec->pipe_fds);
    free(exec);
}

static void collect_command(t_exex *exec, int start, int end)
{
    int i, j, cmd_size;

    cmd_size = 0;
    for (i = start; i < end && exec->tokens[i].token; i++)
        if (exec->tokens[i].flag == TOKEN_WORD)
            cmd_size++;
    exec->cmd_with_flags = malloc(sizeof(char *) * (cmd_size + 1));
    if (!exec->cmd_with_flags)
        exit(1);
    j = 0;
    for (i = start; i < end && exec->tokens[i].token; i++)
        if (exec->tokens[i].flag == TOKEN_WORD)
            exec->cmd_with_flags[j++] = ft_strdup(exec->tokens[i].token);
    exec->cmd_with_flags[j] = NULL;
}

static void execute_command(t_exex *exec, char **env, int start, int end)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if (handle_redirections(exec, start, end) == -1)
        exit(1);
    heredoc(exec, start, end);

    if (exec->cmd_with_flags[0] && is_builtin(exec->cmd_with_flags[0]))
    {
        run_builtin(exec->cmd_with_flags, &env);
        free_exec(exec);
        exit(0);
    }
    else
    {
        execute_absolute_path(exec, env);
        execute_relative_path(exec, env);
        printf("%s: command not found\n", exec->cmd_with_flags[0]);
        free_exec(exec);
        exit(127);
    }
}

void setup_pipes(t_exex *exec)
{
    int i;

    if (exec->pipe_count == 0)
        return;
    exec->pipe_fds = malloc(sizeof(int) * 2 * exec->pipe_count);
    if (!exec->pipe_fds)
        exit(1);
    for (i = 0; i < exec->pipe_count; i++)
        if (pipe(exec->pipe_fds + i * 2) == -1)
        {
            perror("pipe");
            exit(1);
        }
}

void close_pipes(t_exex *exec)
{
    int i;

    if (exec->pipe_count == 0)
        return;
    for (i = 0; i < 2 * exec->pipe_count; i++)
        close(exec->pipe_fds[i]);
}

void execution(t_arr *arr, char **env)
{
    t_exex *exec;
    int i, start, cmd_count;

    exec = malloc(sizeof(t_exex));
    if (!exec)
        return;
    exec->tokens = arr;
    exec->token_count = 0;
    while (arr[exec->token_count].token)
        exec->token_count++;
    exec->cmd_with_flags = NULL;
    exec->paths = NULL;
    exec->path = NULL;
    exec->ex_code = NULL;

    // Count pipes and commands
    exec->pipe_count = 0;
    for (i = 0; arr[i].token; i++)
        if (arr[i].flag == TOKEN_PIPE)
            exec->pipe_count++;
    cmd_count = exec->pipe_count + 1;
    exec->pids = malloc(sizeof(pid_t) * cmd_count);
    if (!exec->pids)
    {
        free_exec(exec);
        return;
    }

    // Setup pipes
    setup_pipes(exec);

    // Execute each command in the pipeline
    start = 0;
    for (i = 0, exec->cmd_index = 0; exec->cmd_index < cmd_count; exec->cmd_index++)
    {
        int end = start;
        while (end < exec->token_count && arr[end].token && arr[end].flag != TOKEN_PIPE)
            end++;
        
        collect_command(exec, start, end);

        signal(SIGINT, SIG_IGN);
        exec->pids[exec->cmd_index] = fork();
        if (exec->pids[exec->cmd_index] == 0)
        {
            if (exec->pipe_count > 0)
            {
                if (exec->cmd_index > 0)
                    dup2(exec->pipe_fds[(exec->cmd_index - 1) * 2], 0);
                if (exec->cmd_index < cmd_count - 1) 
                    dup2(exec->pipe_fds[exec->cmd_index * 2 + 1], 1);
                close_pipes(exec);
            }
            execute_command(exec, env, start, end);
        }
        start = end + 1;
        if (exec->cmd_with_flags)
        {
            for (int j = 0; exec->cmd_with_flags[j]; j++)
                free(exec->cmd_with_flags[j]);
            free(exec->cmd_with_flags);
            exec->cmd_with_flags = NULL;
        }
    }

    close_pipes(exec);
    for (i = 0; i < cmd_count; i++)
        waitpid(exec->pids[i], NULL, 0);
}