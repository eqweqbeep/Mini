
#include "../builtins/builtins.h"
#include "exec.h"

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

void execute_absolute_path(t_exex *exec , char **env) {
	if(exec->cmd_with_flags[0][0] == '/' || (exec->cmd_with_flags[0][0] == '.' && exec->cmd_with_flags[0][1] == '/')) {
		if(access(exec->cmd_with_flags[0] , X_OK) == 0) 
		{
			if(execve(exec->cmd_with_flags[0] , exec->cmd_with_flags , env))
			{	
				write(2 , "error : execve\n" , 16);
				exit(1);
			}	
		} else {
			printf("%s : cmd not found cz of access \n" , exec->cmd_with_flags[0]);
			exit(127);
		}
	}
}
// this func will be used for absolute path
void execute_relative_path(t_exex *exec , char **env) {
	int i = 0;
	exec->paths = extract_paths(env , exec);
	while(exec->paths && exec->paths[i]) {
		exec->path = join_by_order(exec->paths[i] , '/' , exec->cmd_with_flags[0]);
		if(access(exec->path , X_OK | F_OK) == 0) 
			if(execve(exec->path , exec->cmd_with_flags , env) == -1) {
				write(2 , "error : exceve \n" , 17);
			exit(1);
		} 
		i++;
	}
}

int handle_redirections(t_exex *exec)
{
	int i = 0;
	int fd;

	while (exec->cmd_with_flags[i])
	{
		if (strcmp(exec->cmd_with_flags[i], ">") == 0)
		{
			fd = open(exec->cmd_with_flags[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror("open >"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			exec->cmd_with_flags[i] = NULL; // truncate args
			break;
		} else if (strcmp(exec->cmd_with_flags[i], "<") == 0)
		{
			fd = open(exec->cmd_with_flags[i + 1], O_RDONLY);
			if (fd < 0)
				return (perror("open <"), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			exec->cmd_with_flags[i] = NULL;
			break;
		}
		i++;
	}
	return 0;
}


// void check_if_is_builtins(t_exex *exec , char **env) {
// 	if(is_builtin(exec->cmd_with_flags[0])) {
// 		run_builtin(exec->cmd_with_flags , &env);
// 		return;
// 	}
// }



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

