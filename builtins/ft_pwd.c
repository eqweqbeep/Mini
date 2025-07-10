
#include "builtins.h"

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
