/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_int_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:16:15 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:05:03 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbrv2(int nb)
{
	char	x;

	if (nb >= 10)
		ft_putnbrv2(nb / 10);
	x = (nb % 10) + '0';
	ft_putchar(x);
}

static int	n_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnbrz(int nb, t_flag_list flags, int field_width)
{
	if (nb == -2147483648)
	{
		ft_putnstr("-2147483648", 11);
		return ;
	}
	if (nb > 0 && flags.plus == 1 && flags.zero != 1)
		ft_putchar('+');
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (flags.zero == 1 && flags.precision == '\0')
	{
		if (flags.plus == 1 && nb > 0)
			ft_putchar('+');
		ft_putnchars('0', field_width);
	}
	while (flags.precision > n_digits(nb))
	{
		ft_putchar('0');
		flags.precision--;
	}
	ft_putnbrv2(nb);
}

static int	get_field_width(int argument, t_flag_list flags)
{
	int	field_width;
	int	number_len;

	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (flags.fmw);
	number_len = n_digits(argument);
	if (flags.precision > number_len)
		number_len = flags.precision;
	field_width = flags.fmw - number_len;
	if (flags.plus == 1 || flags.space == 1 || argument < 0)
		field_width--;
	if (field_width < 0)
		return (0);
	return (field_width);
}

void	spec_int(t_flag_list flags, int argument)
{
	int	field_width;

	field_width = get_field_width(argument, flags);
	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (ft_putnchars(' ', field_width));
	if (flags.space == 1 && flags.plus != 1 && argument >= 0)
		ft_putchar(' ');
	if (flags.dot == 1)
		flags.zero = 0;
	if (flags.minus == 1)
	{
		flags.zero = 0;
		ft_putnbrz(argument, flags, field_width);
		ft_putnchars(' ', field_width);
	}
	else
	{
		if (flags.zero != 1)
			ft_putnchars(' ', field_width);
		ft_putnbrz(argument, flags, field_width);
	}
	return ;
}
