#include "exec.h"
#include "../main_prog/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
// here we need to create the pipe 
// so what i know about pipe 
// i need to create to childs process to manage the read end and the write end
void piping(char *line , char **env) {
    char **cmds = ft_split(line , '|');
    if(!cmds && !cmds[0] && !cmds[1])
        execution(line , env);
    // here i need to create tow file (d) like read end , and write end
    int fd[2];
    // here to clarify if the pipe func fail and at the same time start it
    if(pipe(fd) == -1)
        printf("error setup pipe\n");
    // to create this communication it must each process do only one task 
    int pid1 = fork();
    if(pid1 == 0) {
        // here its pretty siimple what i need is to create duplicatio of file
        dup2(fd[1] , 1);
        close(fd[0]);
        close(fd[1]);
        execution(cmds[0] , env);
        exit(1);
    }
    // here is the second child
    int pid2 = fork();
    if(pid2 == 0) {
        
        dup2(fd[0] , 0);
        close(fd[0]);
        close(fd[1]);
        execution(cmds[0] , env);
        exit(1);
    }
        close(fd[0]);
        close(fd[0]);
        waitpid(pid1, NULL, 0);
	    waitpid(pid2, NULL, 0);
}