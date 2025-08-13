/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:19:23 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/07 18:16:46 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>

#define SYNTAX_CASES "\002\003\004\005\006"
#define REDIRS "\003\004\005\006"

static int	syntax_error(t_tokens *t)
{
	if (t && t->flag == TOKEN_PIPE)
		return (printf("%s\n", SYNTAX_ERR), 1);
	while (t && t->next)
	{
		if (t->flag == TOKEN_PIPE && t->next->flag == TOKEN_PIPE)
			return (printf("%s\n", SYNTAX_ERR), 1);
		if (ft_strchr(REDIRS, t->flag) && t->next->flag != TOKEN_WORD)
			return (printf("%s\n", SYNTAX_ERR), 1);
		t = t->next;
	}
	if (t && (t->flag == TOKEN_PIPE || ft_strchr(REDIRS, t->flag)))
		return (printf("%s\n", SYNTAX_ERR), 1);
	return (0);
}

static int	flags(char *s)
{
	if (ft_strchr(CASES, *s))
	{
		if (*s == '|')
			return (TOKEN_PIPE);
		else if (*s == '>')
		{
			if (*(s + 1) == *s)
				return (TOKEN_APPEND);
			return (TOKEN_REDIRECT_OUT);
		}
		else if (*s == '<')
		{
			if (*(s + 1) == *s)
				return (TOKEN_HEREDOC);
			return (TOKEN_REDIRECT_IN);
		}
	}
	return (TOKEN_WORD);
}

static t_tokens	*re_assign_flags(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (ft_strchr(FILE_OP, tmp->flag))
		{
			tmp = tmp->next;
			tmp->flag = TOKEN_FILENAME;
		}
		else if (tmp->flag == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			tmp->flag = TOKEN_DELIMITER;
		}
		else
			tmp = tmp->next;
	}
	return (tokens);
}

static t_tokens	*assign_flags(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp->flag = flags(tmp->string);
		tmp = tmp->next;
	}
	if (syntax_error(tokens))
		return (free_tokens(tokens), NULL);
	return (re_assign_flags(tokens));
}

t_list	*input_analysis(char *line)
{
	t_tokens	*tokens;
	t_list		*list;

	tokens = split_and_store(line);
	tokens = assign_flags(tokens);
	if (!tokens)
		return (NULL);
	tokens = ft_expand(tokens);
	list = tokens_to_list(tokens);
	return (list);
}
