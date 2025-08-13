/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:28:03 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/09 23:53:44 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>

int	validate_quotes(char *line)
{
	int	i;
	int	current_quote;

	i = 0;
	current_quote = 0;
	while (line[i])
	{
		if (current_quote == 0)
		{
			if (line[i] == '\'' || line[i] == '\"')
				current_quote = line[i];
		}
		else
		{
			if (line[i] == current_quote)
				current_quote = 0;
		}
		i++;
	}
	return (current_quote != 0);
}

int	check_input(char *line)
{
	char	*s;
	t_info	*info;

	s = line;
	if (!line || !*line)
		return (free(line), 1);
	else if (validate_quotes(line))
	{
		info = static_info();
		info->exit_status = 2;
		return (printf("%s\n", SYNTAX_ERR), free(line), 1);
	}
	else
	{
		while (ft_strchr(WHITESPACES, *line) && *line)
			line++;
		if (!*line)
			return (free(s), 1);
	}
	return (0);
}
