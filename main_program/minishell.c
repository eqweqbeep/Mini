
#include "minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
// here on signal part there is somethings dosent handled 
// like Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
// also there is another case when ...
void setup_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    signal(SIGQUIT, SIG_IGN); 
} 

void	create_prompt(t_shell *shell)
{	
	setup_signals();
	while (1)
	{
		shell->line = readline("\033[95mCrounShell >$\033[0m");
		  if (shell->line == NULL)
        {
            write(1, "exit\n", 5);
            exit(0);
        }
		heredoc(shell->line);
		if (*shell->line)
			execution(shell->line , shell->env);
			//  piping(shell->line, shell->env);
		add_history(shell->line);
	}
	write(1, "exit\n", 5);
}

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