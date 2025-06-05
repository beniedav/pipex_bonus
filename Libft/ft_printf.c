/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:04 by badou             #+#    #+#             */
/*   Updated: 2024/12/07 18:37:41 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_numflags(char const *chunk, t_flag_list *flags, int i)
{
	if (chunk[i] >= '1' && chunk[i] <= '9')
	{
		flags->fmw = atoi(&chunk[i]);
		while (ft_isdigit(chunk[i]))
			i++;
	}
	if (chunk[i] == '.')
	{
		flags->dot = 1;
		i++;
		flags->precision = atoi(&chunk[i]);
		while (ft_isdigit(chunk[i]))
			i++;
	}
	if (haschar(chunk[i], "cspdiuxX%"))
		flags->specifier = chunk[i];
	return (i);
}

static int	get_flags(char const *chunk, t_flag_list *flags)
{
	int		i;
	char	endchars[20];

	ft_strlcpy(endchars, "cspdiuxX%123456789.", 20);
	i = 1;
	if (!haschar(chunk[i], "#0-+ "))
		return (get_numflags(chunk, flags, i));
	while (!haschar(chunk[i], endchars))
	{
		if (chunk[i] == '#')
			flags->hash = 1;
		else if (chunk[i] == '0')
			flags->zero = 1;
		else if (chunk[i] == '-')
			flags->minus = 1;
		else if (chunk[i] == ' ')
			flags->space = 1;
		else if (chunk[i] == '+')
			flags->plus = 1;
		i++;
	}
	return (get_numflags(chunk, flags, i));
}

static int	process_arg(t_flag_list flags, va_list args, char specifier)
{
	if (specifier == 'c')
		spec_char(flags, va_arg(args, int));
	else if (specifier == 's')
		spec_str(flags, va_arg(args, char *));
	else if (specifier == 'p')
		spec_point(flags, va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		spec_int(flags, va_arg(args, int));
	else if (specifier == '%')
		ft_putchar('%');
	else if (specifier == 'u')
		spec_unsigned(flags, va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		spec_hex(flags, va_arg(args, unsigned int));
	else
		return (-1);
	return (1);
}

static int	check(const char *chunk, int i)
{
	if (chunk[i] != '%')
		return (0);
	i++;
	while (haschar(chunk[i], "+- 0#"))
		i++;
	if (chunk[i] >= '1' && chunk[i] <= '9')
	{
		while (ft_isdigit(chunk[i]))
			i++;
	}
	if (chunk[i] == '.')
	{
		i++;
		while (ft_isdigit(chunk[i]))
			i++;
	}
	if (chunk[i] && haschar(chunk[i], "cspdiuxX%"))
		return (1);
	return (0);
}

int	ft_printf(char const *string, ...)
{
	va_list		args;
	int			i;
	t_flag_list	flags;
	int			res;

	va_start(args, string);
	i = 0;
	while (string[i])
	{
		ft_memset(&flags, 0, sizeof(flags));
		if (check(string, i))
		{
			i += get_flags(&string[i], &flags);
			process_arg(flags, args, flags.specifier);
		}
		else
			ft_putchar(string[i]);
		if (protect(-3) < 0)
			return (-1);
		i++;
	}
	res = protect(-3);
	protect(-2);
	return (res);
}
