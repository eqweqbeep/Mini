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
static void collect_command(t_exex *exec, int start, int end)
{
    int i, j, cmd_size;

    cmd_size = 0;
    i = start;
    while (i < end && exec->tokens[i].token) {
        if (exec->tokens[i].flag == TOKEN_WORD)
            cmd_size++;
        i++;
    }
    exec->cmd_with_flags = malloc(sizeof(char *) * (cmd_size + 1));
    if (!exec->cmd_with_flags)
        exit(1);
    j = 0;
    i = start;
    while (i < end && exec->tokens[i].token) {
        if (exec->tokens[i].flag == TOKEN_WORD)
            exec->cmd_with_flags[j++] = ft_strdup(exec->tokens[i].token);
        exec->cmd_with_flags[j] = NULL;
        i++;
    }
}
void execute_command(t_exex *exec, char **env, int start, int end)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if (handle_redirections(exec, start, end) == -1)
        exit(1);

    heredoc(exec, start, end);

    if (exec->cmd_with_flags[0] && is_builtin(exec->cmd_with_flags[0])) {
        run_builtin(exec->cmd_with_flags, &env);
        exit(0);
    } else {
        execute_absolute_path(exec, env);
        execute_relative_path(exec, env);
        printf("%s: command not found\n", exec->cmd_with_flags[0]);
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
    i = 0;
    while (i < exec->pipe_count) {
        if (pipe(exec->pipe_fds + i * 2) == -1) {
            perror("pipe");
            exit(1);
        }
        i++;
    }
}

void close_pipes(t_exex *exec)
{
    int i;

    i = 0;
    if (exec->pipe_count == 0)
        return;
    while (i < 2 * exec->pipe_count) {
        close(exec->pipe_fds[i]);
        i++;
    }
}


void wait_for_children(t_exex *exec, int cmd_count)
{
    for (int i = 0; i < cmd_count; i++)
        waitpid(exec->pids[i], NULL, 0);
}

int find_command_end(t_arr *arr, int start, int token_count)
{
    int end = start;
    while (end < token_count && arr[end].token && arr[end].flag != TOKEN_PIPE)
        end++;
    return end;
}

void execute_pipeline(t_exex *exec, char **env, int cmd_count)
{
    int start = 0;
    for (exec->cmd_index = 0; exec->cmd_index < cmd_count; exec->cmd_index++)
    {
        int end = find_command_end(exec->tokens, start, exec->token_count);
        collect_command(exec, start, end);
        signal(SIGINT, SIG_IGN);

        exec->pids[exec->cmd_index] = fork();
        if (exec->pids[exec->cmd_index] == 0)
            handle_child(exec, env, start, end, cmd_count);

        start = end + 1;
        cleanup_cmd_flags(exec);
    }
}

void execution(t_arr *arr, char **env)
{
    t_exex *exec;
    int cmd_count;

    if (!allocate_exec(&exec, arr))
        return;

    cmd_count = exec->pipe_count + 1;
    if (!allocate_pids(exec, cmd_count))
        return;

    setup_pipes(exec);
    execute_pipeline(exec, env, cmd_count);
    close_pipes(exec);
    wait_for_children(exec, cmd_count);
}

void init_exec(t_exex *exec, t_arr *arr)
{
    int i = 0;

    exec->tokens = arr;
    exec->token_count = 0;
    while (arr[exec->token_count].token)
        exec->token_count++;

    exec->cmd_with_flags = NULL;
    exec->paths = NULL;
    exec->path = NULL;
    exec->ex_code = NULL;
    exec->pipe_count = 0;

    for (i = 0; arr[i].token; i++)
        if (arr[i].flag == TOKEN_PIPE)
            exec->pipe_count++;
}

int allocate_exec(t_exex **exec_ptr, t_arr *arr)
{
    *exec_ptr = malloc(sizeof(t_exex));
    if (!*exec_ptr)
        return 0;
    init_exec(*exec_ptr, arr);
    return 1;
}

int allocate_pids(t_exex *exec, int cmd_count)
{
    exec->pids = malloc(sizeof(pid_t) * cmd_count);
    return (exec->pids != NULL);
}

void handle_child(t_exex *exec, char **env, int start, int end, int cmd_count)
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

void cleanup_cmd_flags(t_exex *exec)
{
    if (exec->cmd_with_flags)
    {
        for (int j = 0; exec->cmd_with_flags[j]; j++)
            free(exec->cmd_with_flags[j]);
        free(exec->cmd_with_flags);
        exec->cmd_with_flags = NULL;
    }
}
