
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

// void built_ins(t_exex *exec ,char **env) {

// }
// this func is for execute only relative path
void execute_relative_path(t_exex *exec , char **env) {
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
void execute_absolute_path(t_exex *exec , char **env) {
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
		execute_relative_path(exec , env);
		// if (exec->cmd_with_flags[0][0] == '/' || 
		//    (exec->cmd_with_flags[0][0] == '.' && exec->cmd_with_flags[0][1] == '/')) {
		// 	if (access(exec->cmd_with_flags[0], F_OK | X_OK) == 0) {
		// 		execve(exec->cmd_with_flags[0], exec->cmd_with_flags, env);
		// 		perror("execve");
		// 		exit(EXIT_FAILURE);
		// 	} else {
		// 		printf("%s : command not found\n", exec->cmd_with_flags[0]);
		// 		exit(127);
		// 	}
		// }
		// exec->paths = extract_paths(env, exec);
		// while (exec->paths && exec->paths[i]) {
		// 	exec->path = join_by_order(exec->paths[i], '/', exec->cmd_with_flags[0]);
		// 	if (access(exec->path, F_OK | X_OK) == 0) {
		// 		if (execve(exec->path, exec->cmd_with_flags, env) == -1)
		// 			perror("execve");
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	free(exec->path);
		// 	i++;
		// }
		execute_absolute_path(exec , env);
		 printf("%s : command not found\n",exec->cmd_with_flags[0]);
		 exit(127);
	} else {
		waitpid(exec->pid, NULL, 0);
	}
}




// typedef struct s_exex {
// 	pid_t	pid;
// 	char	**paths;
// 	char	**cmd_with_flags;
// 	char	*path;
// }	t_exex;


// impleentation of pipe logic and waiting to define pipe 
void piping(char *line , char **env) {
	t_piping *content = malloc(sizeof(t_piping));
	t_exex *exec = malloc(sizeof(t_exex));
	if(!content || !exec)
		perror("xxxxxxxx\n");
	// 2 fd 0 for writeend and 1 for readend 
	//  add double * char 
	exec->cmd_with_flags = ft_split(line , '|');
	if(!exec->cmd_with_flags[0]  || !exec->cmd_with_flags[1] || !exec->cmd_with_flags[2]) {
		execution(line , env);
		return;
	}
	if(pipe(content->fd) == -1)
		write(2 , "error : pipe failed \n" , 21);
	// for 1st pid1 ill fork to create a child that will execute the 1st cmd 
	content->pid1 = fork();
	if(content->pid1 == 0) {
		dup2(content->fd[1] , 1);
		// i must close the 2 gates of the pipe fd 0 and 1
		close(content->fd[0]);
		close(content->fd[1]);
		execution(line , env);
	} else {
		// wait 1st child till end
		waitpid(content->pid1 , NULL , 0);
	}
	// here is the 2nd child that will control my second cmd which mean box it into a child proc
	content->pid2 = fork();
	if(content->pid2 == 0) {
		dup2(content->fd[0] , 0);
		close(content->fd[0]);
		close(content->fd[1]);
		execution(line , env);
	} else {
		//wait 2nd child till end
		waitpid(content->pid2 , NULL , 0);
	}
	// then close all gates of fd
	close(content->fd[0]);
	close(content->fd[1]);

}