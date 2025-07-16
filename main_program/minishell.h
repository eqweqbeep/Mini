
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
typedef struct s_M_S {
	char	*line;
	char	**env;
}	t_shell;

void	create_prompt(t_shell *shell);
void	execution(char *line, char **env);
void piping(char *line , char **env);
void heredoc(char *line);
#endif
