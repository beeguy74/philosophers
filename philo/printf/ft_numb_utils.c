/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:14:56 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:04:13 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	count_i(t_format *zh)
{
	int			l;
	long int	tmp;

	l = 0;
	tmp = zh->numb;
	if (tmp < 0)
	{
		zh->flags |= FLG_MIN;
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		l++;
		tmp = tmp / 10;
	}
	return (l);
}

int	int_prec(t_format *zh)
{
	if (zh->precision <= zh->count)
		zh->precision = 0;
	else
		zh->precision -= zh->count;
	return (0);
}

int	int_wid(t_format *zh)
{
	if (zh->width <= (zh->count + zh->precision))
		zh->width = 0;
	else
		zh->width -= zh->count + zh->precision;
	return (0);
}

int	check_flg_min(t_format *zh)
{
	if (!(zh->flags & FLG_MIN))
		return (0);
	if (zh->width > 0)
		zh->width--;
	return (0);
}

int	print_flg_min(t_format *zh)
{
	if (!(zh->flags & FLG_MIN))
		return (0);
	zh->res++;
	ft_putchar_fd('-', 1);
	return (0);
}
