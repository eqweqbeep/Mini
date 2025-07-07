
#include "minishell.h"


// here create infinite loop that always keep prompt open 
// then if line got some data execute them 
// NEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED
// here i need a function that check 1st for if parsing do execution and this is 
// our 1st meet point tokinize that and do what ever now i will link execution with input
// without parsing so the data that i need on my execution is line that has been tokenized 
// into whatever they are  special symbol or a word or ... and env
// now i let this managed so i will create a directory that contain execution stuff
// same as you create a DIR name it parse and do your stuff to keep things managed 
// thanks for your understanding do your shite we have like only one week to handle
// a lot of things 
void	create_prompt(t_shell *shell)
{	
	while (1)
	{
		shell->line = readline("CrounShell >$");
			execution(shell->line, shell->env);
		if(!shell->line)
				continue;
			add_history(shell->line);		
	}
	write(1, "exit\n", 5);
}

// this is the mother function 
// create the main struct that contain only line to read from prompt  its size is 16 from now i dont now on the few coming days
// and duplication of env
// to let the things managed i need to call only one function from mother
// which create the prompt 
int	main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	t_shell	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = env;
	create_prompt(shell);
	return (0);
}
