/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_hex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:20:10 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:04:56 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_digits(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_puthex(unsigned int nb, t_flag_list flags)
{
	int		x;
	char	base[17];

	x = 0;
	if (flags.specifier == 'X')
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	else
		ft_strlcpy(base, "0123456789abcdef", 17);
	if (nb >= 16)
		ft_puthex(nb / 16, flags);
	x = nb % 16;
	ft_putchar(base[x]);
}

static void	ft_puthexz(unsigned int nb, t_flag_list flags, int field_width)
{
	int	precision;

	precision = flags.precision;
	if (flags.hash == 1)
	{
		ft_putchar('0');
		ft_putchar(flags.specifier);
	}
	if (flags.zero == 1)
		ft_putnchars('0', field_width);
	while (precision > hex_digits(nb))
	{
		ft_putchar('0');
		precision--;
	}
	if (nb == 4294967295u)
	{
		if (flags.specifier == 'X')
			ft_putnstr("FFFFFFFF", 8);
		else
			ft_putnstr("ffffffff", 8);
		return ;
	}
	ft_puthex(nb, flags);
}

static int	get_field_widthx(unsigned int argument, t_flag_list flags)
{
	int	field_width;
	int	hash;
	int	number_len;

	hash = 0;
	number_len = hex_digits(argument);
	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (flags.fmw);
	if (flags.hash == 1)
		hash = 2;
	if (flags.precision > number_len)
		number_len = flags.precision;
	field_width = flags.fmw - number_len - hash;
	if (field_width < 0)
		return (0);
	return (field_width);
}

void	spec_hex(t_flag_list flags, unsigned int argument)
{
	int	field_width;

	field_width = get_field_widthx(argument, flags);
	if (flags.precision == 0 && flags.dot == 1 && argument == 0)
		return (ft_putnchars(' ', field_width));
	if (flags.dot == 1)
		flags.zero = 0;
	if (flags.minus == 1)
	{
		flags.zero = '\0';
		ft_puthexz(argument, flags, field_width);
		ft_putnchars(' ', field_width);
	}
	else
	{
		if (flags.zero != 1)
			ft_putnchars(' ', field_width);
		ft_puthexz(argument, flags, field_width);
	}
	return ;
}
