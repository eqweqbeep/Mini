
#include "builtins.h"

int	ft_cd(char **args)
{
	if (!args[1])
	{
		write(2, "cd: missing argument\n", 22);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
