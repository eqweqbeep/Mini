/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 05:23:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void look_for_builtins(t_list *list , char **env) {
    if(is_builtin(list->cmds[0])) {
            run_builtin(list->cmds, &env);
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
	while (1)
	{
		line = readline(PROMPT);
		history(line);
		if (check_input(line))
			continue ;
		list = input_analysis(line);
        look_for_builtins(list , env);
		print_command_list(list);
        // execution(list , env);
	}
	return (0);
}
