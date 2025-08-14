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

        node = ft_malloc(sizeof(t_list));
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

        node = ft_malloc(sizeof(t_rediraction));
	node->prev = NULL;
	node->next = NULL;
        node->token = ft_strdup(tokens->next->string);
	node->type = tokens->flag;
        node->fd = -1;
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
	t_list  *list;
        t_list  *tmp;
        t_tokens        *head;

	list = NULL;
        head = tokens;
	while (tokens)
	{
		tmp = new_node(&list);
		i = 0;
                tmp->cmds = ft_malloc(sizeof(char *) * (count_words(tokens) + 1));
		while (tokens && tokens->flag != TOKEN_PIPE)
		{
			if (tokens->flag == TOKEN_WORD)
				tmp->cmds[i++] = ft_strdup(tokens->string);
			else if (ft_strchr(RED, tokens->flag))
				add_rediraction(&tmp->rediraction, tokens);
			tokens = tokens->next;
		}
		tmp->cmds[i] = NULL;
		if (tokens && tokens->flag == TOKEN_PIPE)
			tokens = tokens->next;
	}
        free_tokens(head);
        return (list);
}

void    free_command_list(t_list *list)
{
        t_list          *next;
        t_rediraction   *r_next;
        int             i;

        while (list)
        {
                next = list->next;
                if (list->cmds)
                {
                        i = 0;
                        while (list->cmds[i])
                                ft_free(list->cmds[i++]);
                        ft_free(list->cmds);
                }
        while (list->rediraction)
        {
                r_next = list->rediraction->next;
                if (list->rediraction->fd >= 0)
                        close(list->rediraction->fd);
                ft_free(list->rediraction->token);
                ft_free(list->rediraction);
                list->rediraction = r_next;
        }
                while (list->rediraction)
                {
                        r_next = list->rediraction->next;
                        ft_free(list->rediraction->token);
                        ft_free(list->rediraction);
                        list->rediraction = r_next;
                }
                ft_free(list);
                list = next;
        }
}
