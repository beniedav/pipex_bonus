/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_unsigned_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:17:45 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:05:27 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbrv2_u(unsigned int nb)
{
	char	x;

	if (nb >= 10)
		ft_putnbrv2_u(nb / 10);
	x = (nb % 10) + '0';
	ft_putchar(x);
}

static int	n_digits_u(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnbrz_u(unsigned int nb, t_flag_list flags, int field_width)
{
	if (flags.zero == 1 && flags.precision == '\0')
		ft_putnchars('0', field_width);
	while (flags.precision > n_digits_u(nb))
	{
		ft_putchar('0');
		flags.precision--;
	}
	ft_putnbrv2_u(nb);
}

static int	get_field_width_u(unsigned int argument, t_flag_list flags)
{
	int	field_width;
	int	number_len;

	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (flags.fmw);
	number_len = n_digits_u(argument);
	if (flags.precision > number_len)
		number_len = flags.precision;
	field_width = flags.fmw - number_len;
	if (field_width < 0)
		return (0);
	return (field_width);
}

void	spec_unsigned(t_flag_list flags, unsigned int argument)
{
	int	field_width;

	field_width = get_field_width_u(argument, flags);
	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (ft_putnchars(' ', field_width));
	if (flags.dot == 1)
		flags.zero = 0;
	if (flags.minus == 1)
	{
		flags.zero = 0;
		ft_putnbrz_u(argument, flags, field_width);
		ft_putnchars(' ', field_width);
	}
	else
	{
		if (flags.zero != 1)
			ft_putnchars(' ', field_width);
		ft_putnbrz_u(argument, flags, field_width);
	}
	return ;
}
