/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:49:30 by tphung            #+#    #+#             */
/*   Updated: 2021/08/06 16:54:07 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	check_int(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '+' || content[i] == '-')
		i++;
	while (content[i])
	{
		if (!ft_isdigit(content[i]))
			return (1);
		i++;
	}
	return (0);
}

int	validator(char *numb, int ord, void *all)
{
	int		*content;

	if (check_int(numb))
		return (1);
	content = ft_mem_atoi(numb);
	if (!content)
		return (1);
	*(int *)(all + ord * 4) = *content;
	free (content);
	content = NULL;
	return (0);
}

int	get_args(int argc, char **argv, t_all *all)
{
	int	i;
	int	res;

	i = 0;
	if (argc < 5 || argc > 6 || !argv || !*argv)
		return (1);
	res = validator(argv[i], i, (void *)all);
	i++;
	while (!res && i < argc - 1)
	{
		res = validator(argv[i], i, (void *)all);
		i++;
	}
	return (res);
}
