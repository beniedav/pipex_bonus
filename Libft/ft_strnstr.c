/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:01:37 by badou             #+#    #+#             */
/*   Updated: 2024/10/05 16:07:26 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lenlittle;
	size_t	i_j[2];

	i_j[0] = 0;
	if (*little == '\0')
		return ((char *)big);
	if (!*big)
		return (NULL);
	lenlittle = 0;
	while (little[lenlittle] != '\0')
		lenlittle++;
	while (i_j[0] + lenlittle <= len)
	{
		i_j[1] = 0;
		while (i_j[1] < lenlittle)
		{
			if (big[i_j[0] + i_j[1]] != little[i_j[1]])
				break ;
			i_j[1]++;
		}
		if (i_j[1] == lenlittle)
			return ((char *)(big + i_j[0]));
		i_j[0]++;
	}
	return (NULL);
}
