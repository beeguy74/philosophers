/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:24:48 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:07:54 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	str_prec(t_format *zh)
{
	int		l;

	l = ft_strlen(zh->type_str);
	if (zh->precision >= l || zh->precision < 0)
		zh->precision = l;
	else
		l = zh->precision;
	zh->type_str = ft_substr((char const *)zh->type_str, 0, (size_t)l);
	if (!(zh->type_str))
		return (-1);
	return (0);
}

int	fill_write(char n, int numb, t_format *zh)
{
	int		i;

	i = numb;
	if ((zh->flags & FLG_TWO) && (n == 'c'))
	{
		if (!(zh->flags & FLG_ONE))
			n = '0';
	}
	if (n == 'c')
		n = ' ';
	while (i-- > 0)
	{
		ft_putchar_fd(n, 1);
		zh->res++;
	}
	return (0);
}

int	ft_write(t_format *zh)
{
	char		stop;
	const char	*printstr;
	int			i;

	stop = '%';
	printstr = zh->str;
	i = 0;
	if (zh->type_str)
	{
		stop = '\0';
		printstr = zh->type_str;
	}
	while (*(printstr) != stop && *(printstr) != '\0')
	{
		ft_putchar_fd(*(printstr), 1);
		printstr++;
		i++;
	}
	if (stop == '%')
		zh->str += i;
	zh->res += i;
	printstr = 0;
	return (0);
}

int	proc_char(t_format *zh)
{
	if (zh->type != 'c')
		return (0);
	if (zh->width < 1)
		zh->width = 1;
	if (zh->flags & FLG_ONE)
	{
		ft_putchar_fd(va_arg(zh->ap, int), 1);
		fill_write('c', zh->width - 1, zh);
		zh->res++;
	}
	else
	{
		fill_write('c', zh->width - 1, zh);
		ft_putchar_fd(va_arg(zh->ap, int), 1);
		zh->res++;
	}
	return (0);
}

int	proc_str(t_format *zh)
{
	int		l;

	l = 0;
	if (zh->type != 's')
		return (0);
	zh->type_str = va_arg(zh->ap, char *);
	if (!(zh->type_str))
		zh->type_str = "(null)";
	if (str_prec(zh) < 0)
		return (-1);
	l = ft_strlen(zh->type_str);
	if (zh->width < l)
		zh->width = l;
	if (zh->flags & FLG_ONE)
	{
		ft_write(zh);
		fill_write('c', zh->width - l, zh);
	}
	else
	{
		fill_write('c', zh->width - l, zh);
		ft_write(zh);
	}
	return (0);
}
