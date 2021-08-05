/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:58:22 by tphung            #+#    #+#             */
/*   Updated: 2021/08/05 18:35:02 by tphung           ###   ########.fr       */
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
		if (main->phil->num_eat == main->all->must_eat)
		{
			return (NULL);
		}
		if (death_time)
		{
			main->all->flag = 1;
			sem_wait(main->all->sem_prnt);
			printf("%-7d %d is dead\n", death_time, main->phil->name);
			// ft_sem_print("is dead", death_time, main->phil->name, main->all->sem_prnt);
			sem_post(main->all->sem_dth);
			exit(1);
		}
	}
	return (NULL);
}

int	waitpid_forall(pid_t *pids, t_all *all)
{
	int	i;
	int	stat;

	i = 0;
	while (i < all->numb)
	{
		//kill(pids[i], SIGINT);
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
