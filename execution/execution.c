/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/19 03:08:05 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//filename="file with spaces.txt"
//cat < $filename   # This gives "ambiguous redirect"
#include "../builtins/builtins.h"
#include "exec.h"

void execution(char *line, char **env) {
	// int i = 0;
	t_exex *exec = malloc(sizeof(t_exex));
	if (!exec)
		return;

	exec->cmd_with_flags = ft_split(line, ' ');
	// dont care about builtins if you handle what you know you should handle 
	// they will handled automatically
	if (is_builtin(exec->cmd_with_flags[0])) {
		run_builtin(exec->cmd_with_flags, &env);
		return;
	}
	signal(SIGINT, SIG_IGN);
	exec->pid = fork();
	if (exec->pid == 0) {
		signal(SIGINT , SIG_DFL);
		heredoc(line);
		if (handle_redirections(exec) == -1)
				exit(1);
		execute_absolute_path(exec , env);
		execute_relative_path(exec , env);
		printf("%s : command not found\n",exec->cmd_with_flags[0]);
		exit(127);
	} else {
		waitpid(exec->pid, NULL, 0);
	}
	// exit(0);
}
