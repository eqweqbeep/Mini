
#include "builtins.h"
// here some cases i need to handle 
// CrounShell >$echo "-n" hola 
// "-n" hola
// must return :  Hola$>
// CrounShell >$echo      \n hola
 // must return  n hola
 // $>
 // there is a lot of things i should handle
 // exit status $? must handled 
int	ft_echo(char **args)
{
	int	i = 1;
	int	new_l = 1;

	if (args[1] && !strcmp(args[1], "-n"))
	{
		new_l = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_l)
		write(1, "\n", 1);
	return (0);
}
