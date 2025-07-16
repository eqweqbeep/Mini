#include "exec.h"

int handle_redirections(t_exex *exec)
{
	int i = 0;
	int fd;

	while (exec->cmd_with_flags[i])
	{
		if (ft_strncmp(exec->cmd_with_flags[i], ">" , 1) == 0)
		{
			fd = open(exec->cmd_with_flags[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror("open >"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			exec->cmd_with_flags[i] = NULL;
			break;
		} else if (ft_strncmp(exec->cmd_with_flags[i], "<" , 1) == 0)
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