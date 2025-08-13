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


int look_for_builtins(t_list *list , char **env) {
    if(is_builtin(list->cmds[0])) {
            run_builtin(list->cmds, &env);
            return 1;
        }
        return 0;
}

int check_what_to_execute(t_list *list , char **env) {
    if(!look_for_builtins(list , env))
            return 0;
        return 1;
}
void execution(t_list *exec , char **env) {
signal(SIGINT, SIG_IGN);
	exec->pid = fork();
    (void)env;
	if (exec->pid == 0) {
		signal(SIGINT , SIG_IGN);
		signal(SIGINT , SIG_DFL);
		// heredoc(line);
		// if (handle_redirections(exec) == -1)
		// 		exit(1);
		execute_absolute_path(exec , env);
		execute_relative_path(exec , env);
		 printf("%s : command not found\n",exec->cmds[0]);
		 exit(127);
		printf("%s : command not found\n",exec->cmds[0]);
		exit(127);
	} else {
		waitpid(exec->pid, NULL, 0);
	}
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
        check_what_to_execute(list , env);
        execution(list , env);
		print_command_list(list);
	}
	return (0);
}
