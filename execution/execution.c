
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
	exec->pid = fork();
	if (exec->pid == 0) {
		if (handle_redirections(exec) == -1)
				exit(1);
		execute_absolute_path(exec , env);
		execute_relative_path(exec , env);
		 printf("%s : command not found\n",exec->cmd_with_flags[0]);
		 exit(127);
	} else {
		waitpid(exec->pid, NULL, 0);
	}
}
