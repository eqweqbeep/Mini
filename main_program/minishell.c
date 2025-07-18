/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 17:21:12 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



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