/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/26 15:46:37 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time_ms(t_timeval *init_time)
{
	t_timeval	timeval;
	int			elaps_time;
	int			usec;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	usec = (timeval.tv_usec - init_time->tv_usec);
	elaps_time = (timeval.tv_sec - init_time->tv_sec) * 1000;
	elaps_time += usec / 1000;
	return (elaps_time);
}

int	init_struct(t_all *all, t_timeval *init_time)
{

	if (gettimeofday(init_time, NULL))
		return (1);
	*all = (t_all){
		.die_time = 0,
		.eat_time = 0,
		.sleep_time = 0,
		.numb = 0,
		.must_eat = 0,
		.init_time = init_time
	};
	return (0);
}

int	main(int ac, char **av)
{
	t_timeval	timeval;
	t_all		all;

	if (init_struct(&all, &timeval))
		return (1);
	ft_printf("seconds = %d \n", elapsed_time_ms(all.init_time));
	if (get_args(ac, av + 1, &all))
		return (1);
	ft_printf("ARGs = %d %d %d %d \n", all.numb, all.die_time, \
			all.eat_time, all.sleep_time);
	return (0);
}