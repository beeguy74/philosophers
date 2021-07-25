/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numb_procs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:03:23 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:03:40 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	proc_int(t_format *zh)
{
	if (zh->type != 'd' && zh->type != 'i')
		return (0);
	zh->numb = (va_arg(zh->ap, int));
	zh->count = count_i(zh);
	zh->type_str = ft_itoa(zh->numb);
	if (!(zh->type_str))
		return (-1);
	print_digit(zh);
	return (0);
}

int	proc_proc(t_format *zh)
{
	if (zh->type != '%')
		return (0);
	if (zh->width < 1)
		zh->width = 1;
	if (zh->flags & FLG_ONE)
	{
		ft_putchar_fd('%', 1);
		fill_write('c', zh->width - 1, zh);
	}
	else
	{
		fill_write('c', zh->width - 1, zh);
		ft_putchar_fd('%', 1);
	}
	zh->res++;
	return (0);
}

int	proc_unsigned(t_format *zh)
{
	if (zh->type != 'u')
		return (0);
	zh->numb = (va_arg(zh->ap, unsigned int));
	zh->type_str = ft_uns_itoa(zh->numb);
	if (!(zh->type_str))
		return (-1);
	if (zh->numb == 0)
		zh->count = 0;
	else
		zh->count = ft_strlen(zh->type_str);
	print_digit(zh);
	return (0);
}

int	proc_x(t_format *zh)
{
	if (zh->type != 'x')
		return (0);
	zh->numb = (va_arg(zh->ap, unsigned int));
	zh->type_str = ft_itoa_base(zh->numb, 16);
	if (!(zh->type_str))
		return (-1);
	if (zh->numb == 0)
		zh->count = 0;
	else
		zh->count = ft_strlen(zh->type_str);
	print_digit(zh);
	return (0);
}

int	proc_upx(t_format *zh)
{
	if (zh->type != 'X')
		return (0);
	zh->numb = (va_arg(zh->ap, unsigned int));
	zh->type_str = ft_itoa_base(zh->numb, 16);
	if (!(zh->type_str))
		return (-1);
	toupper_str(zh);
	if (zh->numb == 0)
		zh->count = 0;
	else
		zh->count = ft_strlen(zh->type_str);
	print_digit(zh);
	return (0);
}
