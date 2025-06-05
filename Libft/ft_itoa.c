/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:13:37 by badou             #+#    #+#             */
/*   Updated: 2024/10/04 20:58:58 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static void	reverse(char *str, int length)
{
	size_t	start;
	size_t	end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static int	n_digits(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	handle_edge(int *n, int *sign, char **result)
{
	if (*n == 0)
	{
		(*result)[0] = '0';
		(*result)[1] = '\0';
		return (1);
	}
	else if (*n == -2147483648)
	{
		ft_strcpy(*result, "-2147483648\0");
		return (1);
	}
	if (*n < 0)
	{
		*sign = 1;
		*n *= -1;
	}
	return (0);
}

char	*ft_itoa(int n) // handle overflow
{
	int		i;
	int		count;
	int		sign;
	char	*result;

	i = 0;
	count = n_digits(n);
	sign = 0;
	result = (char *)malloc((count + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (handle_edge(&n, &sign, &result))
		return (result);
	while (n > 0)
	{
		result[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (sign)
		result[i++] = '-';
	reverse(result, count);
	result[i] = '\0';
	return (result);
}
