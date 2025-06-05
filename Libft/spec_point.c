/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_point_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:58:13 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:05:09 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	point_digits(unsigned long int n)
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
	return (i + 2);
}

void	ft_putpoint(unsigned long int nb, t_flag_list flags)
{
	int		x;
	char	base[17];

	x = 0;
	ft_strlcpy(base, "0123456789abcdef", 17);
	if (nb >= 16)
		ft_putpoint(nb / 16, flags);
	x = nb % 16;
	ft_putchar(base[x]);
}

void	ft_putpointz(unsigned long int nb, t_flag_list flags, int field_width)
{
	int	precision;

	precision = flags.precision;
	ft_putnstr("0x", 2);
	if (flags.zero == 1)
		ft_putnchars('0', field_width);
	while (precision > point_digits(nb))
	{
		ft_putchar('0');
		precision--;
	}
	ft_putpoint(nb, flags);
}

static int	get_field_widthp(unsigned long int argument, t_flag_list flags)
{
	int	field_width;
	int	number_len;

	number_len = point_digits(argument);
	field_width = flags.fmw - number_len;
	if (field_width < 0)
		return (0);
	return (field_width);
}

void	spec_point(t_flag_list flags, void *vargument)
{
	int					field_width;
	unsigned long int	argument;

	argument = (unsigned long int)vargument;
	field_width = get_field_widthp(argument, flags);
	if (vargument == NULL)
	{
		spec_str(flags, "(nil)");
		return ;
	}
	if (flags.minus == 1)
	{
		flags.zero = '\0';
		ft_putpointz(argument, flags, field_width);
		ft_putnchars(' ', field_width);
	}
	else
	{
		if (flags.zero != 1)
			ft_putnchars(' ', field_width);
		ft_putpointz(argument, flags, field_width);
	}
	return ;
}
