/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 18:08:26 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cat < $filename   # This gives "ambiguous redirect"
#include "../builtins/builtins.h"
#include "minishell.h"

void execution(t_arr *arr, char **env)
{
    t_exex *exec = malloc(sizeof(t_exex));
    if (!exec)
        return;

    // Collect command and arguments from TOKEN_WORD
    int i = 0, j = 0, cmd_size = 0;
    while (arr[i].token)
    {
        if (arr[i].flag == TOKEN_WORD)
            cmd_size++;
        i++;
    }
    exec->cmd_with_flags = malloc(sizeof(char *) * (cmd_size + 1));
    i = 0;
    while (arr[i].token)
    {
        if (arr[i].flag == TOKEN_WORD)
            exec->cmd_with_flags[j++] = arr[i].token;
        i++;
    }
    exec->cmd_with_flags[j] = NULL;

    // Check for builtins
    if (is_builtin(exec->cmd_with_flags[0]))
    {
        run_builtin(exec->cmd_with_flags, &env);
        return;
    }

    signal(SIGINT, SIG_IGN);
    exec->pid = fork();
    if (exec->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
     
        i = 0;
        while (arr[i].token)
        {
            if (arr[i].flag == TOKEN_HEREDOC && arr[i + 1].token)
            {
                heredoc(arr[i + 1].token); 
                i++;
            }
            // else if (arr[i].flag == TOKEN_REDIRECT_OUT && arr[i + 1].token)
            // {
            //     int fd = open(arr[i + 1].token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            //     if (fd < 0)
            //         exit(1);
            //     dup2(fd, 1);
            //     close(fd);
            //     i++;
            // }
            else if (arr[i].flag == TOKEN_APPEND && arr[i + 1].token)
            {
                int fd = open(arr[i + 1].token, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0)
                    exit(1);
                dup2(fd, 1);
                close(fd);
                i++;
            }
            else if ((arr[i].flag == TOKEN_REDIRECT_IN && arr[i + 1].token) || (arr[i].flag == TOKEN_REDIRECT_OUT && arr[i + 1].token))
            {
                handle_redirections(exec);
            //     int fd = open(arr[i + 1].token, O_RDONLY);
            //     if (fd < 0)
            //         exit(1);
            //     dup2(fd, 0);
            //     close(fd);
            //     i++;
            }
            i++;
        }

        execute_absolute_path(exec, env);
        execute_relative_path(exec, env);
        printf("%s : command not found\n", exec->cmd_with_flags[0]);
        exit(127);
    }
    else
    {
        waitpid(exec->pid, NULL, 0);
        free(exec->cmd_with_flags); 
        free(exec);
    }
}

// void execution(char *line, char **env) {
// 	// int i = 0;
// 	t_exex *exec = malloc(sizeof(t_exex));
// 	if (!exec)
// 		return;

// 	exec->cmd_with_flags = ft_split(line, ' ');
// 	// dont care about builtins if you handle what you know you should handle 
// 	// they will handled automatically
// 	if (is_builtin(exec->cmd_with_flags[0])) {
// 		run_builtin(exec->cmd_with_flags, &env);
// 		return;
// 	}
	
// 	signal(SIGINT, SIG_IGN);
// 	exec->pid = fork();
// 	if (exec->pid == 0) {
// 		signal(SIGINT , SIG_DFL);
// 		heredoc(line);
// 		if (handle_redirections(exec) == -1)
// 				exit(1);
// 		execute_absolute_path(exec , env);
// 		execute_relative_path(exec , env);
// 		printf("%s : command not found\n",exec->cmd_with_flags[0]);
// 		exit(127);
// 	} else {
// 		waitpid(exec->pid, NULL, 0);
// 	}
// 	// exit(0);
// }
