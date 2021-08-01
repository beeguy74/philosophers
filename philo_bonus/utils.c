/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:58:22 by tphung            #+#    #+#             */
/*   Updated: 2021/08/01 15:08:00 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, int when_asleep, long long int init_time)
{
	while (time > elapsed_time_ms(init_time) - when_asleep)
		usleep(50);
}

int	peace_death(t_main *main)
{
	int	time_elapsed;
	int	death_time;

	time_elapsed = elapsed_time_ms(main->all->init_time);
	death_time = time_elapsed - main->phil->actual_eat_time;
	if (death_time - main->all->die_time > 0)
		return (time_elapsed);
	return (0);
}

void	*death_loop(void *args)
{
	int		death_time;
	t_main	*main;

	main = (t_main *)args;
	death_time = 0;
	while (!death_time)
	{
		death_time = peace_death(main);
		if (main->phil->num_eat == main->all->must_eat || main->all->flag)
			return (NULL);
		if (death_time)
		{
			sem_post(main->all->sem_dth);
			break ;
		}
	}
	printf("%-7d %d is dead\n", death_time, main->phil->name);
	return (NULL);
}

int	waitpid_forall(pid_t *pids, int num)
{
	int	i;
	int	stat;

	i = 0;
	while (i < num)
	{
		waitpid(pids[i], &stat, 0);
		i++;
	}
	return (0);
}

int	elapsed_time_ms(long long int init_time)
{
	t_timeval	timeval;
	int			elaps_time;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	elaps_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - init_time;
	return (elaps_time);
}
