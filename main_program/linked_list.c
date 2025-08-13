/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:42:02 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/06 22:26:47 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>

t_env	*arr_list(char **env)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (env[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->s = ft_substr(env[i], ft_strlen(env[i]));
		if (!node->s)
			return (free(node), NULL);
		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}
