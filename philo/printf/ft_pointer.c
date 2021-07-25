/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:30:23 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:03:17 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int	print_hex(t_format *zh)
{
	if (zh->pointer_numb == 0 && zh->precision >= 0)
		zh->type_str[2] = '\0';
	if (zh->precision == 0 && zh->pointer_numb == 0)
	{
		zh->type_str[2] = '\0';
		zh->count = 2;
		int_wid(zh);
	}
	else if (zh->precision < 0 && zh->pointer_numb == 0)
	{
		zh->count = 3;
		zh->precision = 0;
		int_wid(zh);
	}
	else
	{
		int_prec(zh);
		int_wid(zh);
	}
	final_int_write(zh);
	return (0);
}

int	proc_p(t_format *zh)
{
	char	*tmp;
	int		len_tmp;

	if (zh->type != 'p')
		return (0);
	zh->pointer_numb = (va_arg(zh->ap, long unsigned));
	tmp = ft_itoa_hex(zh->pointer_numb);
	if (!(tmp))
		return (-1);
	len_tmp = ft_strlen(tmp);
	zh->type_str = malloc(sizeof(char) * (len_tmp + 3));
	if (!(zh->type_str))
		return (-1);
	zh->type_str[len_tmp + 2] = '\0';
	ft_strlcat(zh->type_str, "0x", len_tmp + 3);
	ft_strlcat(zh->type_str, tmp, len_tmp + 3);
	free(tmp);
	zh->count = ft_strlen(zh->type_str);
	print_hex(zh);
	return (0);
}
