/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:29:31 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  dup_std_fds(int *in, int *out)
{
    *in = dup(STDIN_FILENO);
    *out = dup(STDOUT_FILENO);
    if (*in == -1 || *out == -1)
    {
        if (*in != -1)
            close(*in);
        if (*out != -1)
            close(*out);
        return (1);
    }
    return (0);
}

static void restore_std_fds(int in, int out)
{
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    close(in);
    close(out);
}

int     check_what_to_execute(t_list *list, char ***env)
{
    t_info  *info;
    int     saved_in;
    int     saved_out;

    if (list->next || !is_builtin(list->cmds[0]))
        return (0);
    if (dup_std_fds(&saved_in, &saved_out)
        || handle_redirections(list) == -1)
    {
        restore_std_fds(saved_in, saved_out);
        static_info()->exit_status = 1;
        return (1);
    }
    info = static_info();
    info->exit_status = run_builtin(list->cmds, env);
    restore_std_fds(saved_in, saved_out);
    return (1);
}

void    history(char *line)
{
    if (!line || !*line)
        return ;
    add_history(line);
}

void    initialise_info(char **env)
{
    t_info  *info;

    info = static_info();
    info->env = arr_list(env);
    info->exit_status = 0;
}

static void shell_loop(char **env)
{
    char    *line;
    t_list  *list;

    while (1)
    {
        line = readline(PROMPT);
        history(line);
        if (check_input(line))
            continue ;
        list = input_analysis(line);
        if (!list)
        {
            static_info()->exit_status = 258;
            continue ;
        }
        prepare_heredocs(list);
        if (!check_what_to_execute(list, &env))
            execution(list, env);
        print_command_list(list);
        free_command_list(list);
    }
}

int     main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    initialise_info(env);
    signals();
    shell_loop(env);
    return (0);
}

