/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:25:58 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:04:30 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	protect(int write)
{
	static int	protector = 0;
	static int	counter = 0;

	if (write == -1)
		protector++;
	else if (write == -2)
		counter = 0;
	else if (write > 0)
		counter++;
	if (protector > 0)
		return (-1);
	return (counter);
}

void	ft_putchar(char c)
{
	protect(write(1, &c, 1));
}

void	ft_putnchars(char c, int times)
{
	int	i;

	i = 0;
	if (times <= 0)
		return ;
	while (i < times)
	{
		ft_putchar(c);
		i++;
	}
}

int	haschar(const char c, const char *str)
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

void	ft_putnstr(char *s, int len)
{
	int	i;

	i = 0;
	while (s[i] && i < len)
	{
		ft_putchar(s[i]);
		i++;
	}
}
