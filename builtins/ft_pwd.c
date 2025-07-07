
#include "builtins.h"
// i need to handle pwd with options 
// like bash: pwd: -p: invalid option
int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(1, cwd, strlen(cwd));
		write(1, "\n", 1);
	}
	else
		perror("pwd");
	return (0);
}
