/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_extraction_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:26:37 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:38:14 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char **extract_paths(char **env, t_list *exec) {
	int i = 0;
	while (env[i]) {
		if (!(ft_strncmp(env[i], "PATH=", 5))) {
			exec->paths = ft_split(env[i] + 5, ':');
			return exec->paths;
		}
		i++;
	}
	return NULL;
}

char *join_by_order(char const *s1, char b_slash, char const *s2) {
	char *str;
	size_t i = 0, j = 0;

	if (!s1 || !s2)
		return NULL;

	str = (char *)malloc(sizeof(char) * (strlen(s1) + 1 + strlen(s2) + 1));
	if (!str)
		return NULL;

	while (s1[j]) 
		str[i++] = s1[j++];
	str[i++] = b_slash;
	j = 0;
	while (s2[j]) str[i++] = s2[j++];
	str[i] = '\0';
	return str;
}