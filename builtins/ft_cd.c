
#include "builtins.h"

int	ft_cd(char **args)
{
	if (!args[1])
	{
		write(2, "[cd] : is only a shortcut for cd /home so\n", 42);
		 return (1);
		// the exit status should be 0
		 exit(0);
	}
	if (chdir(args[1]) != 0)
	{
		write(2,"No such file or directory\n" , 27);
		return (1);
		exit(0);
	}
	return (0);
}
// case 01 chmod folder to 000 and try to enter to it 