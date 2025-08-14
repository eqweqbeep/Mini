/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:20:05 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/04 17:36:01 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>

static int	special_cases(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		return (1);
	if (line[i] == '<' || line[i] == '>')
		if (line[i] == line[i + 1])
			return (2);
	return (1);
}

static int	token_len(char **line)
{
	int		i;
	char	c;

	i = 0;
	while (ft_strchr(WHITESPACES, **line) && (*line)[i])
		(*line)++;
	if (ft_strchr(CASES, (*line)[i]) && (*line)[i])
		return (special_cases(*line));
	while (!ft_strchr(STOPS, (*line)[i]) && (*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			c = (*line)[i++];
			while ((*line)[i] != c)
				i++;
		}
		i++;
	}
	return (i);
}

static t_tokens	*stack_tokens(t_tokens *tokens, char *s)
{
	t_tokens	*new;
	t_tokens	*last;

        new = ft_malloc(sizeof(t_tokens));
	new->string = s;
	new->flag = 0;
	new->next = NULL;
	new->prev = NULL;
	if (!tokens)
		return (new);
	last = tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (tokens);
}

t_tokens	*split_and_store(char *line)
{
	int			len;
	char		*string;
	t_tokens	*tokens;

	tokens = NULL;
	while (*line)
	{
		len = token_len(&line);
		if (len > 0)
		{
			string = ft_substr(line, len);
			if (!string)
				return (free_tokens(tokens), exit(1), NULL);
			tokens = stack_tokens(tokens, string);
		}
		line += len;
	}
	return (tokens);
}
