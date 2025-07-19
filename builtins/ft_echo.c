/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:13 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/13 21:46:13 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"


static int is_valid_n_flag(const char *arg)
{
	if (arg[0] != '-')
		return (0);
	for (int i = 1; arg[i]; i++)
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int ft_echo(char **args)
{
	int i = 1;
	int newline = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}

	if (newline)
		write(1, "\n", 1);

	return (0);
}
