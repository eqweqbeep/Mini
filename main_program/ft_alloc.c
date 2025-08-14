/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:25:56 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/09 23:50:08 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stddef.h>
#include <unistd.h>

void	ft_free_all(void)
{
	t_gc	*curr;
	t_gc	*next;
	t_gc	**list;

	list = static_gc();
	curr = *list;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
			free(curr->ptr);
		free(curr);
		curr = next;
	}
	*list = NULL;
}

int	append_gc(void *ptr)
{
	t_gc	*node;
	t_gc	**list;

	list = static_gc();
	node = malloc(sizeof(t_gc));
	if (!node)
		return (1);
	node->ptr = ptr;
	node->next = *list;
	*list = node;
	return (0);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_free_all();
		write(2, "minishell: malloc failed\n", 26);
		exit(EXIT_FAILURE);
	}
	if (append_gc(ptr))
	{
		free(ptr);
		ft_free_all();
		write(2, "minishell: malloc failed\n", 26);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	ft_free(void *ptr)
{
	t_gc	**list;
	t_gc	*tmp;

	if (!ptr)
		return ;
	list = static_gc();
	while (*list)
	{
		if ((*list)->ptr == ptr)
		{
			tmp = *list;
			*list = tmp->next;
			free(tmp->ptr);
			free(tmp);
			return ;
		}
		list = &((*list)->next);
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
                ft_free(tokens->string);
                ft_free(tokens);
		tokens = tmp;
	}
}
