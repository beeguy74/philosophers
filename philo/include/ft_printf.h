/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:25:42 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 15:49:58 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FLG_NONE	0b00000000
# define FLG_ONE	0b00000001
# define FLG_TWO	0b00000010
# define FLG_PREC	0b10000000
# define FLG_MIN	0b01000000

# include <stdarg.h>
# include "libft.h"

typedef struct		s_format
{
	va_list			ap;
	const char		*str;
	char			*type_str;
	unsigned char	flags;
	int				width;
	int				precision;
	char			type;
	int				res;
	int				count;
	int				numb;
	unsigned long	pointer_numb;
}					t_format;

int					ft_printf(const char *format, ...);
int					parser(t_format *zh);
int					ft_write(t_format *zh);
int					fill_write(char n, int numb, t_format *zh);
int					proc_char(t_format *zh);
int					proc_str(t_format *zh);
int					proc_int(t_format *zh);
int					proc_proc(t_format *zh);
int					proc_unsigned(t_format *zh);
int					proc_x(t_format *zh);
int					proc_upx(t_format *zh);
int					proc_p(t_format *zh);
int					count_i(t_format *zh);
int					int_prec(t_format *zh);
int					int_wid(t_format *zh);
int					print_digit(t_format *zh);
int					toupper_str(t_format *zh);
int					print_flg_min(t_format *zh);
int					check_flg_min(t_format *zh);
int					int_wid(t_format *zh);
int					int_prec(t_format *zh);
int					count_i(t_format *zh);
int					final_int_write(t_format *zh);

#endif
