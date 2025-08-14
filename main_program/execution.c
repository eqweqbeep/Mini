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

void execution(t_list *cmds, char **env)
{
    int     pipe_fd[2];
    int     prev_fd;
    int     cmd_count;
    pid_t   *pids;
    int     i;
    int     status;
    t_info  *info;

    info = static_info();
    cmd_count = list_size(cmds);
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        return ;
    prev_fd = -1;
    i = 0;
    while (cmds)
    {
        if (cmds->next && pipe(pipe_fd) == -1)
        {
            perror("pipe");
            info->exit_status = 1;
            break ;
        }
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            info->exit_status = 1;
            break ;
        }
        if (pids[i] == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            setup_io(prev_fd, pipe_fd, cmds->next != NULL);
            if (handle_redirections(cmds) == -1)
                exit(1);
            if (is_builtin(cmds->cmds[0]))
                exit(run_builtin(cmds->cmds, &env));
            execute_absolute_path(cmds, env);
            execute_relative_path(cmds, env);
            ft_putstr_fd(cmds->cmds[0], 2);
            ft_putendl_fd(": command not found", 2);
            exit(127);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        else
            prev_fd = -1;
        cmds = cmds->next;
        i++;
    }
    if (prev_fd != -1)
        close(prev_fd);
    while (i-- > 0)
    {
        waitpid(pids[i], &status, 0);
        if (i == 0)
            info->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
    free(pids);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   End of execution.c                                 :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */
