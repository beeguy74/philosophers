/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:37:41 by tphung            #+#    #+#             */
/*   Updated: 2021/07/23 20:21:52 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_mem_atoi(const char *str)
{
	long long int	i;
	long long int	mp;
	long long int	res;
	int				*mem_res;

	i = 0;
	res = 0;
	mp = 1;
	mem_res = (int *)malloc(sizeof(int));
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		mp = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		res = ((str[i] - '0') + 10 * res);
		i++;
	}
	if ((res * mp) < -2147483648 || (res * mp > 2147483647) || !mem_res)
		mem_res = NULL;
	else
		*mem_res = res * mp;
	return (mem_res);
}
