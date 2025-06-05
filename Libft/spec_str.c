/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_str_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:21:00 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:05:18 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdio.h>

void	spec_str(t_flag_list flags, char *argument)
{
	int	field_width;
	int	length;

	if (argument == NULL)
	{
		if (flags.dot == 1 && flags.precision < 6)
			argument = "";
		else
			argument = "(null)";
	}
	length = ft_strlen(argument);
	if (flags.dot == 1 && flags.precision < length)
		length = flags.precision;
	field_width = flags.fmw - length;
	if (flags.minus == 1)
	{
		ft_putnstr(argument, length);
		ft_putnchars(' ', field_width);
	}
	else
	{
		ft_putnchars(' ', field_width);
		ft_putnstr(argument, length);
	}
	return ;
}
