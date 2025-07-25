/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 20:46:31 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// t_shell *get_memmo(void){
// 	static t_shell *head;
// 	return &head;
// }

static int	flags(char *s)
{
	if (ft_strchr(CASES, *s))
	{
		if (*s == '|')
			return (TOKEN_PIPE);
		else if (*s == '<')
		{
			if (*(s + 1) == *s)
				return (TOKEN_APPEND);
			return (TOKEN_REDIRECT_IN);
		}
		else if (*s == '>')
		{
			if (*(s + 1) == *s)
				return (TOKEN_HEREDOC);
			return (TOKEN_REDIRECT_OUT);
		}
	}
	return (TOKEN_WORD);
}

static t_arr	*re_assign_flags(t_arr **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[i].token)
	{
		if ((*tokens)[i].flag == TOKEN_HEREDOC && (*tokens)[i + 1].token)
			(*tokens)[i + 1].flag = TOKEN_DELIMITER; 
		else if (ft_strchr(FILE_OP, (*tokens)[i].flag) && (*tokens)[i + 1].token)
			(*tokens)[i + 1].flag = TOKEN_FILENAME;
		i++;
	}
	return (*tokens);
}

static t_arr	*assign_flags(char **arr)
{
	int	i;
	t_arr	*tokens;

	i = 0;
	while (arr[i])
		i++;
	tokens = (t_arr *)malloc(sizeof(t_arr) * (i + 1));
	i = 0;
	while (arr[i])
	{
		tokens[i].token = arr[i];
		tokens[i].flag = flags(arr[i]);
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].flag = 0;
	return (re_assign_flags(&tokens));
}

static void	*input_analysis(char *line)
{
	char	**arr;

	arr = NULL;
	if (check_input(line))
		return (printf("ERR\n"), NULL);
	arr = split_and_stack(line);
	if (!arr || !*arr)
		return (printf("ERR\n"), NULL);
	return ((t_arr *)assign_flags(arr));
}

void create_prompt(t_shell *shell)
{
    t_arr *arr;
    while (1)
    {
		setup_signals();
        shell->line = readline("\033[95mCrounShell >$\033[0m");
        if (shell->line == NULL)
        {
            write(1, "exit\n", 5);
            exit(0);
        }
        if (!check_input(shell->line))
        {
            arr = input_analysis(shell->line);
            if (arr)
            {
                execution(arr, shell->env); // Updated call
            }
        }
        add_history(shell->line);
    }
    write(1, "exit\n", 5);
}

// void	create_prompt(t_shell *shell)
// {	
// 	t_arr	*arr;
// 	while (1)
// 	{
// 		// setup_signals();
// 		shell->line = readline("\033[95mCrounShell >$\033[0m");
// 		  if (shell->line == NULL)
//         {
//             write(1, "exit\n", 5);
//             exit(0);
//         }
// 		if (!check_input(shell->line))
// 		{
// 			arr = input_analysis(shell->line);
// 			// for (int i = 0; arr[i].token; i++)
// 				// printf("token: %s | flag: %d\n", arr[i].token, arr[i].flag);
// 			execution(shell->line , shell->env);
// 		}
// 		// if (*shell->line)
// 			//  piping(shell->line, shell->env);
// 		add_history(shell->line);
// 	}
// 	write(1, "exit\n", 5);
// }

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
