/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:34:32 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:06:09 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	toupper_str(t_format *zh)
{
	int		i;

	i = 0;
	while (zh->type_str[i] != '\0')
	{
		zh->type_str[i] = ft_toupper(zh->type_str[i]);
		i++;
	}
	return (0);
}

int	print_int(t_format *zh)
{
	char	*printstr;

	if (zh->type_str[0] == '-')
		printstr = zh->type_str + 1;
	else
		printstr = zh->type_str;
	ft_putstr_fd(printstr, 1);
	zh->res += ft_strlen(printstr);
	printstr = 0;
	return (0);
}

int	final_int_write(t_format *zh)
{
	check_flg_min(zh);
	if (zh->flags & FLG_ONE)
	{
		print_flg_min(zh);
		fill_write('0', zh->precision, zh);
		print_int(zh);
		fill_write('c', zh->width, zh);
	}
	else
	{
		if (zh->flags & FLG_PREC || !(zh->flags & FLG_TWO))
		{
			fill_write(' ', zh->width, zh);
			print_flg_min(zh);
		}
		else
		{
			print_flg_min(zh);
			fill_write('c', zh->width, zh);
		}
		fill_write('0', zh->precision, zh);
		print_int(zh);
	}
	return (0);
}
