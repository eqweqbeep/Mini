
#include "builtins.h"

// jait-chd@c2r3p13:~/goinfre/minishell$ cd execution/ builtins/
// bash: cd: too many arguments
// jait-chd@c2r3p13:~/goinfre/minishell$ 
// this case in not handled 
// CrounShell >$cd 'execution/'
//cd: No such file or directory
//CrounShell >$
// this case must run normal not only singal quotes also double 
// what ever when i add singal or double on this cases must habe clean run

// we have also this case jait-chd@c2r3p13:~$ cd -
// /home/jait-chd
// jait-chd@c2r3p13:~$ 


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
