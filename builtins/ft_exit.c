
#include "builtins.h"

int	ft_exit(char **args)
{
	int	code = 0;

	write(1, "exit\n", 5);
	if (args[1])
		code = atoi(args[1]);
	exit(code);
}
 