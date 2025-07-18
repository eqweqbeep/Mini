/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 17:21:12 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
#include "../main_program/minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
#include <fcntl.h>
#include <string.h>
// this just a few vars of what i need 
// you can add ...
typedef struct s_exex {
	pid_t	pid;
	char	**paths;
	char	**cmd_with_flags;
	char	*path;
}	t_exex;

typedef struct x {
	int fd[2];
	int pid1 ;
	int pid2;
} t_piping;


char	**extract_paths(char **env, t_exex *exec);
char	*join_by_order(char const *s1, char b_slash, char const *s2);
void	execution(char *line, char **env);

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


