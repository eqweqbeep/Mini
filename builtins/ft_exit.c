
#include "builtins.h"
// this case must give me errro on stderr [exit 666 666]
int	ft_exit(char **args)
{
	int	code = 0;

	write(1, "exit\n", 5);

	if (args[1])
		code = atoi(args[1]);
	// if(!args[1] && !args[2])
	// 	write(2 , "the args must be exit and one exit status\n" , 42);
	exit(code);
}
 