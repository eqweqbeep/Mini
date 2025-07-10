
#include "builtins.h"

int	ft_echo(char **args)
{
	int	i = 1;
	int	nl = 1;

	if (args[1] && !strcmp(args[1], "-n"))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
