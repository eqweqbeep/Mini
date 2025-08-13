/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 05:19:13 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/12 01:03:33 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>

// const char	*get_flag_name(int flag)
// {
// 	if (flag == TOKEN_WORD)
// 		return ("WORD");
// 	if (flag == TOKEN_PIPE)
// 		return ("PIPE");
// 	if (flag == TOKEN_REDIRECT_IN)
// 		return ("REDIRECT_IN");
// 	if (flag == TOKEN_REDIRECT_OUT)
// 		return ("REDIRECT_OUT");
// 	if (flag == TOKEN_APPEND)
// 		return ("APPEND");
// 	if (flag == TOKEN_HEREDOC)
// 		return ("HEREDOC");
// 	if (flag == TOKEN_FILENAME)
// 		return ("FILENAME");
// 	if (flag == TOKEN_DELIMITER)
// 		return ("DELIMITER");
// 	return ("UNKNOWN");
// }
//
// void	print_command_list(t_list *list)
// {
// 	int				i;
// 	t_rediraction	*r;
//
// 	printf("=== [ PARSED COMMAND STRUCTURE ] ===\n");
// 	while (list)
// 	{
// 		printf("┌─── Command Node ──────────────────────────────\n");
// 		for (i = 0; list->cmds && list->cmds[i]; i++)
// 			printf("│ CMD[%d]: \"%s\"\n", i, list->cmds[i]);
// 		r = list->rediraction;
// 		while (r)
// 		{
// 			printf("│ REDIR: %-12s -> \"%s\"%s\n", get_flag_name(r->type),
// 				r->token, r->ambiguous ? "  [ambiguous]" : "");
// 			r = r->next;
// 		}
// 		printf("└───────────────────────────────────────────────\n");
// 		list = list->next;
// 	}
// }
// #include <stdio.h>
// #define RESET "\033[0m"
// #define CYAN "\033[36m"
// #define GREEN "\033[32m"
// #define YELLOW "\033[33m"
// #define MAGENTA "\033[35m"
// #define BOLD "\033[1m"
// #define UNDERLINE "\033[4m"
//
// void	print_command_list(t_list *list)
// {
// 	int				i;
// 	t_rediraction	*red;
// 	int				cmd_count;
// 				const char *type = "(unknown)";
//
// 	cmd_count = 0;
// 	printf(BOLD CYAN "\n┌─── Command Pipeline Overview ───┐\n" RESET);
// 	while (list)
// 	{
// 		printf(BOLD GREEN "\n├─ Command Block [%d] ──────────────\n" RESET,
// 			cmd_count++);
// 		printf(BOLD "│\n│  Command(s):\n" RESET);
// 		if (!list->cmds || !list->cmds[0])
// 			printf("│    (none)\n");
// 		else
// 		{
// 			for (i = 0; list->cmds[i]; i++)
// 				printf("│    - %s\n", list->cmds[i]);
// 		}
// 		printf(BOLD "│\n│  Redirections:\n" RESET);
// 		red = list->rediraction;
// 		if (!red)
// 			printf("│    (none)\n");
// 		else
// 		{
// 			while (red)
// 			{
// 				if (red->type == TOKEN_REDIRECT_IN)
// 					type = "<";
// 				else if (red->type == TOKEN_REDIRECT_OUT)
// 					type = ">";
// 				else if (red->type == TOKEN_APPEND)
// 					type = ">>";
// 				else if (red->type == TOKEN_HEREDOC)
// 					type = "<<";
// 				printf("│    %s %s", type, red->token);
// 				if (red->ambiguous)
// 					printf(" " YELLOW "(ambiguous)" RESET);
// 				printf("\n");
// 				red = red->next;
// 			}
// 		}
// 		printf(BOLD "│\n└───────────────────────────────\n" RESET);
// 		list = list->next;
// 	}
// 	printf(BOLD CYAN "\n⌞ End of Pipeline ⌝\n" RESET);
// }

#include <stdio.h>

void	print_command_list(t_list *list)
{
	int				i;
	t_rediraction	*redir;
	int				index;

	index = 1;
	while (list)
	{
		printf("┌───────────────────────────────────────────────┐\n");
		printf("│                Command Node %2d                │\n", index++);
		printf("├───────────────────────────────────────────────┤\n");
		if (list->cmds && list->cmds[0])
		{
			printf("│ Commands:\n");
			for (i = 0; list->cmds[i]; i++)
				printf("│   - `%s`\n", list->cmds[i]);
			printf("│\n");
		}
		else
			printf("│ Commands: (none)\n");
		printf("├───────────────────────────────────────────────┤\n");
		if (list->rediraction)
		{
			printf("│ Redirections:\n");
			redir = list->rediraction;
			while (redir)
			{
				printf("│   - \"%s\" (%s)%s\n", redir->token,
					redir->type == TOKEN_REDIRECT_IN ? "input" : redir->type == TOKEN_REDIRECT_OUT ? "output" : redir->type == TOKEN_APPEND ? "append" : redir->type == TOKEN_HEREDOC ? "heredoc" : "unknown",
					redir->ambiguous ? " [ambiguous]" : "");
				redir = redir->next;
			}
		}
		else
			printf("│ Redirections: (none)\n");
		printf("└───────────────────────────────────────────────┘\n\n");
		list = list->next;
	}
}
