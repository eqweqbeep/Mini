/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:04 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/08 17:46:42 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	count_words(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->flag != TOKEN_PIPE)
	{
		if (tokens->flag == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_list	*new_node(t_list **list)
{
	t_list	*node;
	t_list	*tmp;

	node = malloc(sizeof(t_list));
	node->cmds = NULL;
	node->rediraction = NULL;
	node->next = NULL;
	node->prev = NULL;
	if (!*list)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
	return (node);
}

void	add_rediraction(t_rediraction **red, t_tokens *tokens)
{
	t_rediraction	*node;
	t_rediraction	*tmp;

	node = malloc(sizeof(t_rediraction));
	node->prev = NULL;
	node->next = NULL;
	node->token = tokens->next->string;
	node->type = tokens->flag;
	node->ambiguous = 0;
	if ((tokens->next->next && tokens->next->flag == tokens->next->next->flag)
		|| !*tokens->next->string)
		node->ambiguous = 1;
	if (!*red)
		*red = node;
	else
	{
		tmp = *red;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

t_list	*tokens_to_list(t_tokens *tokens)
{
	int		i;
	t_list	*list;
	t_list	*tmp;

	list = NULL;
	while (tokens)
	{
		tmp = new_node(&list);
		i = 0;
		tmp->cmds = (char **)malloc(sizeof(char *) * count_words(tokens) + 1);
		while (tokens && tokens->flag != TOKEN_PIPE)
		{
			if (tokens->flag == TOKEN_WORD)
				tmp->cmds[i++] = tokens->string;
			else if (ft_strchr(RED, tokens->flag))
				add_rediraction(&tmp->rediraction, tokens);
			tokens = tokens->next;
		}
		tmp->cmds[i] = NULL;
		if (tokens && tokens->flag == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (list);
}
