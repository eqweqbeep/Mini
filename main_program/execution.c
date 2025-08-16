/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "minishell.h"

static int list_size(t_list *lst)
{
    int count;

    count = 0;
    while (lst)
    {
        count++;
        lst = lst->next;
    }
    return (count);
}

static void setup_io(int prev_fd, int pipe_fd[2], int has_next)
{
    if (prev_fd != -1)
    {
        dup2(prev_fd, 0);
        close(prev_fd);
    }
    if (has_next)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
    }
}

static int init_pids(t_list *cmds, pid_t **pids, int *prev_fd)
{
    int count;

    count = list_size(cmds);
    *pids = malloc(sizeof(pid_t) * count);
    if (!*pids)
        return (-1);
    *prev_fd = -1;
    return (count);
}

static int prepare_pipe(t_list *cmds, int pipe_fd[2])
{
    t_info *info;

    if (!cmds->next)
        return (0);
    info = static_info();
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        info->exit_status = 1;
        return (-1);
    }
    return (0);
}

static void child_process(t_list *cmds, char ***env, int prev_fd, int pipe_fd[2])
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    setup_io(prev_fd, pipe_fd, cmds->next != NULL);
    if (handle_redirections(cmds) == -1)
        exit(1);
    if (is_builtin(cmds->cmds[0]))
        exit(run_builtin(cmds->cmds, env));
    execute_absolute_path(cmds, *env);
    execute_relative_path(cmds, *env);
    ft_putstr_fd(cmds->cmds[0], 2);
    ft_putendl_fd(": command not found", 2);
    exit(127);
}

static void parent_process(int *prev_fd, t_list *cmds, int pipe_fd[2])
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmds->next)
    {
        close(pipe_fd[1]);
        *prev_fd = pipe_fd[0];
    }
    else
        *prev_fd = -1;
}

static void wait_children(pid_t *pids, int count)
{
    int     i;
    int     status;
    t_info  *info;

    info = static_info();
    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        if (i == count - 1)
        {
            if (WIFEXITED(status))
                info->exit_status = WEXITSTATUS(status);
            else
                info->exit_status = 1;
        }
        i++;
    }
}

static void finalize_execution(int prev_fd, pid_t *pids, int cmd_count)
{
    if (prev_fd != -1)
        close(prev_fd);
    wait_children(pids, cmd_count);
    free(pids);
}

static void run_commands(t_list *cmds, char **env,
        pid_t *pids, int prev_fd)
{
    int     pipe_fd[2];
    int     i;

    i = 0;
    while (cmds)
    {
        if (prepare_pipe(cmds, pipe_fd) == -1)
            break ;
        pids[i] = fork();
        if (pids[i] == -1)
            break ;
        if (pids[i] == 0)
            child_process(cmds, &env, prev_fd, pipe_fd);
        parent_process(&prev_fd, cmds, pipe_fd);
        cmds = cmds->next;
        i++;
    }
    finalize_execution(prev_fd, pids, i);
}

void    execution(t_list *cmds, char **env)
{
    pid_t   *pids;
    int     prev_fd;
    int     cmd_count;

    cmd_count = init_pids(cmds, &pids, &prev_fd);
    if (cmd_count < 0)
        return ;
    run_commands(cmds, env, pids, prev_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   End of execution.c                                 :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

