/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:09:39 by badou             #+#    #+#             */
/*   Updated: 2024/10/11 19:53:52 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	count_substr(const char *s, char c)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*get_substr(const char *s, size_t start, size_t end)
{
	size_t	i;
	size_t	len;
	char	*result;

	if (start >= end)
	{
		result = (char *)malloc(sizeof(char));
		result[0] = '\0';
		return (result);
	}
	i = 0;
	len = end - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	free_helper(char **result, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static void	initialize(size_t *ijse)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		ijse[i] = 0;
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	size_t	i_j_s_e[4];
	char	**result;

	initialize(i_j_s_e);
	result = (char **)ft_calloc((count_substr(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i_j_s_e[0]])
	{
		while (s[i_j_s_e[0]] == c)
			i_j_s_e[0]++;
		i_j_s_e[2] = i_j_s_e[0];
		while (s[i_j_s_e[0]] != c && s[i_j_s_e[0]] != '\0')
			i_j_s_e[0]++;
		i_j_s_e[3] = i_j_s_e[0];
		if (i_j_s_e[2] == i_j_s_e[3])
			break ;
		result[i_j_s_e[1]] = get_substr(s, i_j_s_e[2], i_j_s_e[3]);
		if (!result[i_j_s_e[1]])
			return (free_helper(result, count_substr(s, c)), NULL);
		i_j_s_e[1]++;
	}
	result[i_j_s_e[1]] = NULL;
	return (result);
}
