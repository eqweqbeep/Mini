/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crouns <crouns@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 04:26:55 by crouns           ###   ########.fr       */
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
# include <sys/wait.h>
#include <fcntl.h>

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

typedef struct s_exex {
	pid_t	pid;
	char	**paths;
	char	**cmd_with_flags;
	char	*path;
	char *ex_code;
}	t_exex;

char	**split_and_stack(char *line);
int		check_input(char *line);
char	*ft_strchr(char *s, int c);
void	create_prompt(t_shell *shell);
// void 	piping(char *line , char **env);
void 	setup_signals(void);

//


// typedef struct x {
// 	int fd[2];
// 	int pid1 ;
// 	int pid2;
// } t_piping;


char	**extract_paths(char **env, t_exex *exec);
char	*join_by_order(char const *s1, char b_slash, char const *s2);
void	execution(t_arr *arr, char **env);

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strdup(const char *s);
char *ft_substr(char const *s, unsigned int start, size_t len);
void execute_absolute_path(t_exex *exec , char **env);
void execute_relative_path(t_exex *exec , char **env);
int handle_redirections(t_exex *exec);
void heredoc(char *line);
#endif
