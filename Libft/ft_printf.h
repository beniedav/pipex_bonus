/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:11:47 by badou             #+#    #+#             */
/*   Updated: 2025/05/04 16:05:30 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct FlagList
{
	int		hash;
	int		space;
	int		plus;
	int		minus;
	int		zero;
	int		precision;
	int		fmw;
	int		dot;
	char	specifier;
}			t_flag_list;

int			protect(int write);
int			haschar(const char c, const char *str);
void		ft_putchar(char c);
void		ft_putnchars(char c, int times);
void		ft_putnstr(char *s, int len);
void		spec_int(t_flag_list flags, int argument);
void		spec_unsigned(t_flag_list flags, unsigned int argument);
void		spec_hex(t_flag_list flags, unsigned int argument);
void		spec_str(t_flag_list flags, char *argument);
void		spec_char(t_flag_list flags, int argument);
void		spec_percent(t_flag_list flags, int argument);
void		spec_point(t_flag_list flags, void *argument);
int			ft_printf(char const *string, ...);
#endif
