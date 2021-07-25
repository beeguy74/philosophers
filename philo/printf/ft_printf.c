/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:36:48 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:06:42 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_memdel(void **po)
{
	if (!po || !*po)
		return ;
	free(*po);
	*po = NULL;
}

int	init_zh(t_format *zh)
{
	zh->flags = 0;
	zh->width = 0;
	zh->precision = -1;
	zh->type = 0;
	zh->count = 0;
	zh->numb = 0;
	zh->pointer_numb = 0;
	ft_memdel((void **)&(zh->type_str));
	return (0);
}

int	print_digit(t_format *zh)
{
	if (zh->numb == 0 && zh->precision >= 0)
		zh->type_str[0] = '\0';
	if (zh->precision == 0 && zh->numb == 0)
		zh->type_str[0] = '\0';
	else if (zh->precision < 0 && zh->numb == 0)
	{
		zh->count = 1;
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

int	proc(t_format *zh)
{
	int		ret;

	ret = 0;
	ret = proc_proc(zh);
	ret = proc_char(zh);
	ret = proc_str(zh);
	ret = proc_int(zh);
	ret = proc_unsigned(zh);
	ret = proc_x(zh);
	ret = proc_upx(zh);
	ret = proc_p(zh);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	t_format	zh;

	va_start(zh.ap, format);
	zh.str = format;
	zh.res = 0;
	zh.type_str = 0;
	while (*(zh.str) != '\0')
	{
		init_zh(&zh);
		ft_write(&zh);
		parser(&zh);
		proc(&zh);
	}
	va_end(zh.ap);
	return (zh.res);
}
