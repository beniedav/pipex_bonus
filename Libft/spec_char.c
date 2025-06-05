/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_char_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:24:52 by badou             #+#    #+#             */
/*   Updated: 2024/12/04 18:04:47 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	spec_char(t_flag_list flags, int argument)
{
	int	field_width;

	field_width = flags.fmw - 1;
	if (flags.minus == 0)
	{
		ft_putnchars(' ', field_width);
		ft_putchar(argument);
	}
	else if (flags.minus == 1)
	{
		ft_putchar(argument);
		ft_putnchars(' ', field_width);
	}
	return ;
}
