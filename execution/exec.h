#ifndef EXEC_H
#define EXEC_H

#include "../main_prog/minishell.h"  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct  s_exec 
{
    int pid;
    char	**cmd_with_flags;
	char	**paths;
	char	*path;
} t_exex;

char **extract_paths(char **env , t_exex *exec);
void execution(char *line , char **env);
char	*join_by_order(char const *s1, char b_slash, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void piping(char *line , char **env);


#endif
