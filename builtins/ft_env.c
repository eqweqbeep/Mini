
#include "builtins.h"

int	ft_env(char **env)
{
	int	i = 0;

	while (env[i])
	{
		write(1, env[i], strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
