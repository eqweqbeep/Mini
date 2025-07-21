/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 17:21:12 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>


// Macros
# define PROMPT "~/path$ "
# define WHITESPACES " \t\n\r\v\f"
# define STOPS " \t\n\r\v\f><|"
# define CASES "|<>"
# define FILE_OP "\003\004\005" 
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIRECT_IN 3
# define TOKEN_REDIRECT_OUT 4
# define TOKEN_APPEND 5
# define TOKEN_HEREDOC 6
# define TOKEN_FILENAME 7
# define TOKEN_DELIMITER 8

typedef struct s_list
{
	char			*token;
	int				flag;
	struct s_list	*next;
}					t_list;

typedef struct s_arr
{
	char			*token;
	int				flag;
}					t_arr;

typedef struct s_M_S {
	char	*line;
	char	**env;
}	t_shell;

char	**split_and_stack(char *line);
int		check_input(char *line);
char	*ft_strchr(char *s, int c);
void	create_prompt(t_shell *shell);
void	execution(char *line, char **env);
void 	piping(char *line , char **env);
void 	setup_signals(void);
#endif
