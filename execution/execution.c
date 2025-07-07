
#include "../builtins/builtins.h"
#include "exec.h"
// this function extracts all paths from env 
char **extract_paths(char **env, t_exex *exec) {
	int i = 0;
	while (env[i]) {
		if (!(ft_strncmp(env[i], "PATH=", 5))) {
			exec->paths = ft_split(env[i] + 5, ':');
			return exec->paths;
		}
		i++;
	}
	return NULL;
}
// this function only add to the path a back slash and add the cmd 
// like /usr/bin + / + cmd[ls];
char *join_by_order(char const *s1, char b_slash, char const *s2) {
	char *str;
	size_t i = 0, j = 0;

	if (!s1 || !s2)
		return NULL;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1 + ft_strlen(s2) + 1));
	if (!str)
		return NULL;

	while (s1[j]) 
		str[i++] = s1[j++];
	str[i++] = b_slash;
	j = 0;
	while (s2[j]) str[i++] = s2[j++];
	str[i] = '\0';
	return str;
}

void setup_path(char **env ,t_exex *exec) {
	exec->paths = extract_paths(env ,exec);
}

// this is the same execution functions i did before (you seen it on my github )
// what i add here is 2 functions for built ins but 
// soon i will change this main execution but not now becuze i will wait a lot of things from you
// iam waiting you to define special symbols like redirections and append , heredoc
// quotes ... so dont disapoint me and handle all this 
// if you did this then i must change this main execution function and 
// let it more managed for norm 
// till we meet ill explain this execution now you dont need to know what happend 
// ok now i did a struct that contain all these vars that i need on my execution
// and i still add something else from you you can edit on my struct or just add a new struct then i will see about how to move it 
void execution(char *line, char **env) {
	int i = 0;
	t_exex *exec = malloc(sizeof(t_exex));
	if (!exec) 
		return;
	//check_type_of_cmd(exec , env);
	exec->cmd_with_flags = ft_split(line, ' ');
	// dont care about builtins if you handle what you know you should handle 
	// they will handled automatically
	if (is_builtin(exec->cmd_with_flags[0])) {
		run_builtin(exec->cmd_with_flags, &env);
		return;
	}

	exec->pid = fork();
	if (exec->pid == 0) {
		setup_path(env , exec);
		// exec->paths = extract_paths(env, exec);
		while (exec->paths && exec->paths[i]) {
			 exec->path = join_by_order(exec->paths[i], '/', exec->cmd_with_flags[0]);
			if (access(exec->path, F_OK | X_OK) == 0) {
				if (execve(exec->path, exec->cmd_with_flags, env) == -1)
					perror("execve");
				exit(EXIT_FAILURE);
			}
//			free(exec->path);
			i++;
		}
		printf("%s : command not found\n",exec->cmd_with_flags[0]);
		exit(127);
	} else {
		waitpid(exec->pid, NULL, 0);
	}
}
