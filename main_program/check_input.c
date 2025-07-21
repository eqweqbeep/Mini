/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:19:19 by mokoubar          #+#    #+#             */
/*   Updated: 2025/07/18 00:21:07 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == '\0')
		return (s + i);
	return (NULL);
}


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
			if (line[i] == '\'' || line[i] == '"')
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
	if (!line || !*line)
		return (1);
	if (validate_quotes(line))
		return (1);
	while (ft_strchr(WHITESPACES, *line))
		line++;
	if (!*line)
		return (1);
	return (0);
}
