/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:47:26 by badou             #+#    #+#             */
/*   Updated: 2024/10/03 12:34:57 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptrd;
	const unsigned char	*ptrs;

	if (!dest && !src)
		return (NULL);
	ptrd = (unsigned char *)dest;
	ptrs = (const unsigned char *)src;
	if (ptrd < ptrs)
		while (n--)
			*ptrd++ = *ptrs++;
	else
		while (n--)
			ptrd[n] = ptrs[n];
	return (dest);
}
