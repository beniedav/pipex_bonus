/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:17:26 by badou             #+#    #+#             */
/*   Updated: 2024/10/11 19:31:29 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	i;

	if (nmemb * size > 2147483647)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	result = malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)result)[i] = 0;
		i++;
	}
	return (result);
}
