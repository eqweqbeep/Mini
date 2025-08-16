/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:05 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by ChatGPT         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../main_program/minishell.h"

int is_builtin(char *cmd);
int run_builtin(char **cmd, char ***env);
int ft_echo(char **args);
int ft_cd(char **args);
int ft_pwd(char **args);
int ft_exit(char **args);
int ft_env(char **args, char **env);
int ft_export(char **args, char ***env);
int ft_unset(char **args, char ***env);

#endif
