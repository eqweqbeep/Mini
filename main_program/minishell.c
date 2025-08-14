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

int check_what_to_execute(t_list *list, char **env)
{
    t_info  *info;
    int     saved_stdin;
    int     saved_stdout;

    if (!list->next && is_builtin(list->cmds[0]))
    {
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        if (saved_stdin == -1 || saved_stdout == -1)
        {
            if (saved_stdin != -1)
                close(saved_stdin);
            if (saved_stdout != -1)
                close(saved_stdout);
            static_info()->exit_status = 1;
            return (1);
        }
        if (handle_redirections(list) == -1)
        {
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
            static_info()->exit_status = 1;
            return (1);
        }
        info = static_info();
        info->exit_status = run_builtin(list->cmds, &env);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return (1);
    }
    return (0);
}

void	history(char *line)
{
	if (!line || !*line)
		return ;
	add_history(line);
}

void	initialise_info(char **env)
{
	t_info	*info;

	info = static_info();
	info->env = arr_list(env);
	info->exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*list;

	(void)ac;
	(void)av;
	initialise_info(env);
    signals();
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
                if (!check_what_to_execute(list, env))
                {
                        execution(list, env);
                }
                print_command_list(list);
                free_command_list(list);
        }
        return (0);
}
