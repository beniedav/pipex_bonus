/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:23:18 by badou             #+#    #+#             */
/*   Updated: 2024/10/03 12:38:03 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest_len = i;
	j = 0;
	while (src[j] != '\0')
		j++;
	src_len = j;
	if (size <= dest_len)
		return (size + src_len);
	j = 0;
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
