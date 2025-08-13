/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:58:52 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/12 17:06:09 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	get_variables(char *token, char **string, char **map)
{
	int	len;
	int	tmp;

	while (*token)
	{
		len = get_len(token, 0);
		*string = ft_strjoin(*string, ft_substr(token, len));
		*map = ft_strjoin(*map, fill_str(len, '0'));
		token += len;
		if (!*token)
			break ;
		len = get_var_len(token);
		tmp = len;
		*string = ft_strjoin(*string, ft_getenv(token, &len));
		*map = ft_strjoin(*map, fill_str(len, '1'));
		token += tmp;
	}
	get_len(NULL, 1);
}

// void	append_to_list(t_tokens **tmp, t_split *new_lst)
// {
// }

t_tokens	*ft_expand(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*string;
	char		*map;

	tmp = tokens;
	while (tmp)
	{
		string = NULL;
		map = NULL;
		if (tmp->flag == TOKEN_WORD || tmp->flag == TOKEN_FILENAME)
		{
			get_variables(tmp->string, &string, &map);
			tmp->string = string;
			/* append_to_list(&tmp, split_preserve_quotes(string, map),
				tmp->flag); */
		}
		tmp = tmp->next;
	}
	return (tokens);
}
