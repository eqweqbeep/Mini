#include "exec.h"


void is_built_in(char *line , char **env) {
    if(ft_strncmp(line , "exit" , 4) == 0)
        exit_b_in(line);
    else if(ft_strncmp(line , "echo" , 4) == 0)
        echo_b_in(line);
    else if(ft_strncmp(line , "env" , 3) == 0)
        env_b_in(line);
    else if(ft_strncmp(line , "unset" , 5) == 0)
        unset_b_in(line);
    else if(ft_strncmp(line , "export" , 6) == 0)
        export_b_in(line);
    else if(ft_strncmp(line , "cd" , 2) == 0)
        cd_b_in(line);
    else if(ft_strncmp(line , "pwd" , 3) == 0)
        pwd_b_in(line);

}