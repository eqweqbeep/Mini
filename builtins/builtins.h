/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:05 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/17 02:22:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int		is_builtin(char *cmd);
int		run_builtin(char **cmd, char ***env);
int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_exit(char **args);
int		ft_env(char **env);

#endif
