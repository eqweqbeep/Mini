/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:42:36 by jait-chd         ###   ########.fr       */
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
# include <fcntl.h>
#include "../builtins/builtins.h"
// Macros
# define PROMPT "minishell--> "
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
# define SYNTAX_ERR "minishell: syntax error: invalid or unexpected input"
# define ERR_NEAR_TOKEN "\002\003\004\005\006"
# define RED "\003\004\005\006"
# define ISVAL1 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_?"
# define ISVAL2 "0123456789"


// Structs //
/* for toknization */
typedef struct s_tokens
{
	struct s_tokens			*prev;
	char					*string;
	int						flag;
	struct s_tokens			*next;
}							t_tokens;
typedef struct s_split
{
	char					*string;
	char					*map;
	struct s_split			*next;
}							t_split;
/* struct for rediraction */
typedef struct s_rediraction
{
	struct s_rediraction	*prev;
	char					*token;
	int						type;
        int                                             fd;
	int						ambiguous;
	struct s_rediraction	*next;
}							t_rediraction;
/* final struct */
typedef struct s_list
{
	struct s_list			*prev;
	char					**cmds;
    int             pid;
    char            **paths;
    char            *path;
	t_rediraction			*rediraction;
	struct s_list			*next;
}							t_list;
/* garbge collector */
typedef struct s_gc
{
	void					*ptr;
	struct s_gc				*next;
}							t_gc;
/* for env list */
typedef struct s_env
{
	char					*s;
	struct s_env			*next;
}							t_env;
/* info struct */
typedef struct s_info
{
	t_env					*env;
	int exit_status;
}							t_info;

// Prototypes
t_info						*static_info(void);
t_env						*arr_list(char **env);
t_list						*input_analysis(char *line);
int							ft_strlen(char *s);
int							ft_strncmp(char *s1, char *s2, int n);
char						*ft_substr(char *s, int len);
char						*ft_strchr(char *s, int c);
int							check_input(char *line);
t_tokens					*split_and_store(char *line);
void						free_tokens(t_tokens *tokens);
t_tokens					*variable_expansion(t_tokens *tokens);
t_list						*tokens_to_list(t_tokens *tokens);
void						print_command_list(t_list *list);
void						free_command_list(t_list *list);
t_gc						**static_gc(void);
void						ft_free_all(void);
int							append_gc(void *ptr);
void						*ft_malloc(size_t size);
void						ft_free(void *ptr);
void						free_tokens(t_tokens *tokens);
t_tokens					*ft_expand(t_tokens *tokens);
char						*ft_getenv(char *token, int *len);
char						*ft_strjoin(char *s1, char *s2);
char						*fill_str(int len, char c);
int							get_var_len(char *s);
int							get_len(char *s, int reset);
t_split						*split_preserve_quotes(char *s, char *map);
void    signals(void);
void    execute_absolute_path(t_list *exec, char **env);
void    execute_relative_path(t_list *exec, char **env);
char    **extract_paths(char **env, t_list *exec);
char    *join_by_order(char const *s1, char b_slash, char const *s2);
char **ft_split(char const *s, char c);
char    *ft_strdup(const char *s);
void    ft_putstr_fd(char *s, int fd);
void    ft_putendl_fd(char *s, int fd);
int     handle_redirections(t_list *exec);
int     heredoc(char *delimiter);
void    prepare_heredocs(t_list *exec);
void    execution(t_list *cmds, char **env);
#endif

// void cleanup_cmd_flags(t_exex *exec);
// void handle_child(t_exex *exec, char **env, int start, int end, int cmd_count);
// int allocate_exec(t_exex **exec_ptr, t_arr *arr);
// int allocate_pids(t_exex *exec, int cmd_count);
// void init_exec(t_exex *exec, t_arr *arr);
// void execute_pipeline(t_exex *exec, char **env, int cmd_count);
// void execute_command(t_exex *exec, char **env, int start, int end);
// void wait_for_children(t_exex *exec, int cmd_count);
// void free_exec(t_exex *exec);
// void close_pipes(t_exex *exec);
// void setup_pipes(t_exex *exec);
// char    **split_and_stack(char *line);
// char    *ft_strchr(char *s, int c);
// void    create_prompt(t_shell *shell);
// void    execution(t_arr *arr, char **env);
// size_t  ft_strlen(const char *s);
// char    **ft_split(char const *s, char c);
// int     ft_strncmp(const char *s1, const char *s2, size_t n);
// char    *ft_strdup(const char *s);
// char    *ft_substr(char const *s, unsigned int start, size_t len);
// int     handle_redirections(t_exex *exec, int start, int end);
// void    heredoc(t_exex *exec, int start, int end);
// void    setup_pipes(t_exex *exec);
// void    close_pipes(t_exex *exec);
// void    free_exec(t_exex *exec);
