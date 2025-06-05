/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:24:11 by badou             #+#    #+#             */
/*   Updated: 2024/10/08 20:21:59 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	istrim(const char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	s_e_i[2];
	size_t	j;

	s_e_i[0] = 0;
	s_e_i[1] = ft_strlen(s1);
	while (istrim(s1[s_e_i[0]], set))
		s_e_i[0]++;
	while (s_e_i[1] > s_e_i[0] && istrim(s1[s_e_i[1] - 1], set))
		s_e_i[1]--;
	result = (char *)malloc((s_e_i[1] - s_e_i[0] + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	while (s_e_i[0] < s_e_i[1])
	{
		result[j] = s1[s_e_i[0]];
		s_e_i[0]++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
