/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:49:30 by tphung            #+#    #+#             */
/*   Updated: 2021/07/27 14:56:55 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
