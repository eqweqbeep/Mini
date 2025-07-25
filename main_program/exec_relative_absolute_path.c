/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_relative_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 00:13:27 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_absolute_path(t_exex *exec , char **env) {
	if(exec->cmd_with_flags[0][0] == '/' || (exec->cmd_with_flags[0][0] == '.' && exec->cmd_with_flags[0][1] == '/')) {
		if(access(exec->cmd_with_flags[0] , X_OK) == 0) 
		{
			if(execve(exec->cmd_with_flags[0] , exec->cmd_with_flags , env))
			{	
				write(1 , "error : execve\n" , 16);
				exit(1);
			}	
		} else {
			printf("cmd not found cz of access : %s \n" , exec->cmd_with_flags[0]);
			exit(127);
		}
	}
}
// this func will be used for absolute path
void execute_relative_path(t_exex *exec , char **env) {
	int i = 0;
	exec->paths = extract_paths(env , exec);
	while(exec->paths && exec->paths[i]) {
		exec->path = join_by_order(exec->paths[i] , '/' , exec->cmd_with_flags[0]);
		if(access(exec->path , X_OK | F_OK) == 0) 
			if(execve(exec->path , exec->cmd_with_flags , env) == -1) {
				write(2 , "error : exceve \n" , 17);
			exit(1);
		} 
		i++;
	}
}