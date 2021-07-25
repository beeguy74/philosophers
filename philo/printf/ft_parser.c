/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:11:56 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:05:44 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int	flag_min(t_format *zh)
{
	while (*(zh->str) == '-' && *(zh->str) != '\0')
	{
		zh->flags |= FLG_ONE;
		zh->str++;
	}
	while (*(zh->str) == '0' && *(zh->str) != '\0')
	{
		zh->flags |= FLG_TWO;
		zh->str++;
	}
	if (*(zh->str) == '-')
	{
		flag_min(zh);
	}
	if ((zh->flags & FLG_ONE) && (zh->flags & FLG_TWO))
	{
		zh->flags ^= FLG_TWO;
	}
	return (0);
}

static int	is_digit_atoi(t_format *zh)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((*(zh->str)) != '\0' && (ft_isdigit(*(zh->str))))
	{
		i++;
		zh->str++;
	}
	zh->str -= i;
	if (*(zh->str) == '*')
	{
		zh->str++;
		res = va_arg(zh->ap, int);
	}
	else
		res = ft_atoi(zh->str);
	zh->str += i;
	return (res);
}

int	parser(t_format *zh)
{
	if ((*(zh->str)) == '%')
	{
		zh->str++;
		flag_min(zh);
		zh->width = is_digit_atoi(zh);
		if (zh->width < 0)
		{
			zh->flags |= FLG_ONE;
			zh->width = -zh->width;
			flag_min(zh);
		}
		if ((*(zh->str)) == '.')
		{
			zh->str++;
			zh->precision = is_digit_atoi(zh);
			if (zh->precision >= 0)
				zh->flags = zh->flags | FLG_PREC;
		}
		if (ft_isalpha(*(zh->str)) || *(zh->str) == '%')
		{
			zh->type = *(zh->str);
			zh->str++;
		}
	}
	return (0);
}
