/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 06:23:54 by mokoubar          #+#    #+#             */
/*   Updated: 2025/07/19 06:35:28 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**stack_tokens(char **arr, char *token)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	i = 0;
	if (arr)
		while (arr[len])
			len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i++] = token;
	new_arr[i] = NULL;
	return (new_arr);
}

char	*extract_token(char *line, int len)
{
	int		i;
	char	*token;

	i = 0;
	token = malloc(sizeof(char) * len);
	while (i < len)
	{
		token[i] = line[i];
		i++;
	}
	token [len] = '\0';
	return (token);
}

int	token_lenght(char **line)
{
	int		i;
	char	c;

	i = 0;
	while (ft_strchr(WHITESPACES, **line) && (*line)[i])
		(*line)++;
	if (ft_strchr(CASES, (*line)[i]))
		while (ft_strchr(CASES, (*line)[i]) && (*line)[i])
			i++;
	else
	{
		while (!ft_strchr(STOPS, (*line)[i]) && (*line)[i])
		{
			if ((*line)[i] == '\'' || (*line)[i] == '\"')
			{
				c = (*line)[i++];
				while ((*line)[i++] != c)
					;
			}
			i++;
		}
	}
	return (i);
}

char	**split_and_stack(char *line)
{
	int		len;
	char	*token;
	char	**arr;

	arr = NULL;
	while (*line)
	{
		len = token_lenght(&line);
		if (len > 0)
		{
			token = extract_token(line, len);
			arr = stack_tokens(arr, token);
		}
		line += len;
	}
	return (arr);
}
