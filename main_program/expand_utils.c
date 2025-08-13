/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoubar <mokoubar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:59:57 by mokoubar          #+#    #+#             */
/*   Updated: 2025/08/11 22:02:12 by mokoubar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_len(char *s, int reset)
{
	static int	in_single;
	static int	in_double;
	int			i;

	if (reset)
		return (in_single = in_double = 0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (s[i] == '"' && !in_single)
			in_double = !in_double;
		else if (!in_single && s[i] == '$' && (ft_strchr(ISVAL1, s[i + 1])
				|| s[i + 1] == '?'))
			break ;
		i++;
	}
	return (i);
}

int	get_var_len(char *s)
{
	int	len;

	len = 1;
	if (s[len] == '?')
		return (2);
	while (s[len] && (ft_strchr(ISVAL1, s[len]) || ft_strchr(ISVAL2, s[len])))
		len++;
	return (len);
}

char	*fill_str(int len, char c)
{
	char	*str;
	int		i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

static void	copy_strings(char *result, char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	copy_strings(result, s1, s2);
	free(s1);
	free(s2);
	return (result);
}
