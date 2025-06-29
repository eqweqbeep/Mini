#include "exec.h"

///// the next step is to extract paths from env///////////////
// this function should extract all paths from env
// the idea of the function is cuting all paths and store them 
// 1st i need to while on env and check if env [each inedx in env] is same as PATH= if found
// then i need to split env + 5 (which is PATH=) with : then store them on paths and return 
// return them
char **extract_paths(char **env , t_exex *exec) {
    int i = 0;
    while(env[i]) {
        if(!(ft_strncmp(env[i] , "PATH=" , 5))) {
            exec->paths = ft_split(env[i]+ 5 , ':');
            return exec->paths;
        }
        i++;
    }
    return NULL;
}
// the function is clear which is join a string with another 
// but we add in the middle a back slash thats it
char	*join_by_order(char const *s1, char b_slash, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1 + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = b_slash;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// here is when i started the execution////////////////////////////
// here this is the main function only for (execution part) from it all started 
// this function take the line or cmd and env that i will loop on it 
// and extract the exact path of bin/sbin

void execution(char *line , char **env) {
    t_exex *exec = malloc(sizeof(t_exex));
    if(!exec)
        return;
    int i  = 0;
    exec->pid = fork();
    if(exec->pid == 0) {
        exec->cmd_with_flags = ft_split(line , ' ');
        exec->paths = extract_paths(env , exec);
        // now that i extract all paths by spliting env with : i extracted them all 
        // the next step is to while on each path and join cmd like "ls" 
        // to path in final to have a path like usr/bin/ls
        while(exec->paths[i]) {
            // now that i joined path "like usr/bin " with "/"  and cmd without his flags 
            exec->path = join_by_order(exec->paths[i] , '/' , exec->cmd_with_flags[0]);
            // i need to check access with a sys call that called access 
            if (access(exec->path, F_OK | X_OK) == 0)
		    {
		    	if (execve(exec->path, exec->cmd_with_flags, NULL) == -1)
			    	perror("error on execve func");
			    exit(EXIT_FAILURE);
	    	}
            // increament index to step into another paths and do this instruction if the index is the same path as a cmd
            i++;
        }
    }
}
