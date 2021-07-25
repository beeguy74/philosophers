/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:37:41 by tphung            #+#    #+#             */
/*   Updated: 2021/07/23 18:37:31 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long int	i;
	long long int	mp;
	long long int	res;

	i = 0;
	res = 0;
	mp = 1;
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
	if ((res * mp) < -2147483648)
		res = 0;
	else if ((res * mp > 2147483647))
		res = -1;
	return (res * mp);
}
