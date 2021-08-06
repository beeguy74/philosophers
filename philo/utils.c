/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:35:34 by tphung            #+#    #+#             */
/*   Updated: 2021/08/06 15:38:28 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time_ms(long long int init_time)
{
	t_timeval	timeval;
	int			elaps_time;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	elaps_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - init_time;
	return (elaps_time);
}

void	ft_usleep(int time, int when_asleep, long long int init_time)
{
	usleep(time * 900);
	while (time > elapsed_time_ms(init_time) - when_asleep)
		usleep(50);
}

void	ft_mut_print(t_phil *main, char *mes, long long int time, int name)
{
	pthread_mutex_lock(&main->forks[main->all->numb + 1]);
	printf("%-7d %d %s\n", elapsed_time_ms(time), name, mes);
	pthread_mutex_unlock(&main->forks[main->all->numb + 1]);
}

int	peace_death(t_phil main)
{
	int	time_elapsed;
	int	death_time;

	time_elapsed = elapsed_time_ms(main.all->init_time);
	death_time = time_elapsed - main.actual_eat_time;
	if (death_time - main.all->die_time > 0)
		return (time_elapsed);
	return (0);
}

int	death_loop(t_phil **main)
{
	int	i;

	i = -1;
	while (!(*main)->all->flag)
	{
		if (++i == (*main)->all->numb)
			i = 0;
		(*main)->all->flag = peace_death((*main)[i]);
		if ((*main)[i].num_eat == (*main)->all->must_eat)
			return (0);
	}
	pthread_mutex_lock(&(*main)[i].forks[(*main)->all->numb + 1]);
	printf("%-7d %d is dead\n", (*main)->all->flag, (*main)[i].name);
	return (0);
}
