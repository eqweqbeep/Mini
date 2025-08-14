/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:00:00 by ChatGPT          #+#    #+#             */
/*   Updated: 2025/08/16 23:00:00 by ChatGPT         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../builtins/builtins.h"

static int list_size(t_list *lst)
{
    int size;

    size = 0;
    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return (size);
}

static void close_all_pipes(int **pipes, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

static void child_process(t_list *cmd, int **pipes, int i, int count, char **env)
{
    int j;

    signal(SIGINT, SIG_DFL);
    if (i > 0)
        dup2(pipes[i - 1][0], 0);
    if (i < count - 1)
        dup2(pipes[i][1], 1);
    j = 0;
    while (j < count - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    heredoc(cmd);
    if (handle_redirections(cmd) == -1)
        exit(1);
    if (cmd->cmds && cmd->cmds[0] && is_builtin(cmd->cmds[0]))
        exit(run_builtin(cmd->cmds, &env));
    execute_absolute_path(cmd, env);
    execute_relative_path(cmd, env);
    ft_putstr_fd(cmd->cmds[0], 2);
    ft_putendl_fd(": command not found", 2);
    exit(127);
}

void    execute_pipeline(t_list *cmds, char **env)
{
    int     cmd_count;
    int     i;
    int     status;
    int     **pipes;
    pid_t   *pids;
    t_list  *tmp;
    t_info  *info;

    info = static_info();
    cmd_count = list_size(cmds);
    pipes = NULL;
    if (cmd_count > 1)
    {
        pipes = malloc(sizeof(int *) * (cmd_count - 1));
        i = 0;
        while (i < cmd_count - 1)
        {
            pipes[i] = malloc(sizeof(int) * 2);
            if (pipe(pipes[i]) == -1)
                exit(1);
            i++;
        }
    }
    pids = malloc(sizeof(pid_t) * cmd_count);
    tmp = cmds;
    i = 0;
    while (i < cmd_count)
    {
        pids[i] = fork();
        if (pids[i] == 0)
            child_process(tmp, pipes, i, cmd_count, env);
        tmp = tmp->next;
        i++;
    }
    i = 0;
    if (pipes)
    {
        close_all_pipes(pipes, cmd_count - 1);
        while (i < cmd_count - 1)
            free(pipes[i++]);
        free(pipes);
    }
    i = 0;
    while (i < cmd_count)
    {
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1)
        {
            if (WIFEXITED(status))
                info->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                info->exit_status = 128 + WTERMSIG(status);
        }
        i++;
    }
    free(pids);
}

/* End of pipes.c */
