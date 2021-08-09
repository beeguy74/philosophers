/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:29:39 by tphung            #+#    #+#             */
/*   Updated: 2021/08/09 14:02:36 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_all **all)
{
	t_timeval		*init_time;
	long long int	time;

	init_time = malloc(sizeof(t_timeval));
	if (!init_time || gettimeofday(init_time, NULL))
		return (1);
	time = init_time->tv_sec * 1000 + init_time->tv_usec / 1000;
	free (init_time);
	*all = malloc(sizeof(t_all));
	if (!*all)
		return (1);
	**all = (t_all){
		.die_time = 0,
		.eat_time = 0,
		.sleep_time = 0,
		.numb = 0,
		.must_eat = -1,
		.flag = 0,
		.init_time = time
	};
	return (0);
}

int	init_mutex(pthread_mutex_t **forks, t_all *all, int flag)
{
	pthread_mutex_t	*fork;
	int				i;

	if (flag)
		return (1);
	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (all->numb + 2));
	if (!fork)
		return (1);
	while (i < all->numb + 2)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (1);
		i++;
	}
	*forks = fork;
	return (0);
}

void	repeating_values(t_phil *phil, pthread_mutex_t *forks, t_all *all)
{
	phil->forks = forks;
	phil->all = all;
	phil->actual_eat_time = 0;
	phil->num_eat = 0;
}

int	init_phils(t_phil **phils, t_all *all, pthread_mutex_t *forks, int flag)
{
	int		i;

	if (flag)
		return (1);
	i = 0;
	*phils = (t_phil *)malloc(sizeof(t_phil) * (all->numb));
	if (!*phils)
		return (1);
	while (i < all->numb)
	{
		repeating_values((*phils) + i, forks, all);
		(*phils)[i].name = i + 1;
		if (i == all->numb - 1)
		{
			(*phils)[i].right_fork = 0;
			(*phils)[i].left_fork = i;
		}
		else
		{
			(*phils)[i].right_fork = i;
			(*phils)[i].left_fork = i + 1;
		}
		i++;
	}
	return (0);
}
