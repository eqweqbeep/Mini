/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 17:50:51 by jait-chd         ###   ########.fr       */
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

typedef struct s_arr
{
    char            *token;
    int             flag;
}                   t_arr;

typedef struct s_shell
{
    char    *line;
    char    **env;
}           t_shell;

typedef struct s_exex
{
    pid_t   *pids;          // Array of PIDs for piped commands
    char    **paths;        // PATH environment variable split
    char    **cmd_with_flags; // Command and arguments
    char    *path;          // Resolved command path
    char    *ex_code;       // Exit code (optional)
    t_arr   *tokens;        // Token array from parser
    int     token_count;    // Number of tokens
    int     pipe_count;     // Number of pipes
    int     *pipe_fds;      // Pipe file descriptors
    int     cmd_index;      // Current command index in pipeline
}           t_exex;

void cleanup_cmd_flags(t_exex *exec);
void handle_child(t_exex *exec, char **env, int start, int end, int cmd_count);
int allocate_exec(t_exex **exec_ptr, t_arr *arr);
int allocate_pids(t_exex *exec, int cmd_count);
void init_exec(t_exex *exec, t_arr *arr);
void execute_pipeline(t_exex *exec, char **env, int cmd_count);
void execute_command(t_exex *exec, char **env, int start, int end);
void wait_for_children(t_exex *exec, int cmd_count);
void free_exec(t_exex *exec);
void close_pipes(t_exex *exec);
void setup_pipes(t_exex *exec);
char    **split_and_stack(char *line);
int     check_input(char *line);
char    *ft_strchr(char *s, int c);
void    create_prompt(t_shell *shell);
void    setup_signals(void);
char    **extract_paths(char **env, t_exex *exec);
char    *join_by_order(char const *s1, char b_slash, char const *s2);
void    execution(t_arr *arr, char **env);
size_t  ft_strlen(const char *s);
char    **ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strdup(const char *s);
char    *ft_substr(char const *s, unsigned int start, size_t len);
void    execute_absolute_path(t_exex *exec, char **env);
void    execute_relative_path(t_exex *exec, char **env);
int     handle_redirections(t_exex *exec, int start, int end);
void    heredoc(t_exex *exec, int start, int end);
void    setup_pipes(t_exex *exec);
void    close_pipes(t_exex *exec);
void    free_exec(t_exex *exec);

#endif