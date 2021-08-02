/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/08/02 18:37:11 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_phil *phil, t_all *all)
{
	phil->num_eat++;
	sem_wait(all->sem_prnt);
	if (all->flag)
		return ;
	phil->actual_eat_time = elapsed_time_ms(all->init_time);
	printf("%-7d %d is eating\n", phil->actual_eat_time, phil->name);
	sem_post(all->sem_prnt);
	ft_usleep(all->eat_time, phil->actual_eat_time, all->init_time);
	sem_post(all->sem);
	sem_post(all->sem);
}

void	*eat(void *args)
{
	t_phil			*phil;
	t_all			*all;
	int				time;

	all = ((t_main *)args)->all;
	phil = ((t_main *)args)->phil;
	while (phil->num_eat != all->must_eat)
	{
		sem_wait(all->sem_prnt);
		if (all->flag)
			break ;
		time = elapsed_time_ms(all->init_time);
		printf("%-7d %d is thinking\n", time, phil->name);
		sem_post(all->sem_prnt);
		sem_wait(all->sem);
		sem_wait(all->sem);
		if (all->flag)
			break ;
		is_eating(phil, all);
		sem_wait(all->sem_prnt);
		if (all->flag)
			break ;
		time = elapsed_time_ms(all->init_time);
		printf("%-7d %d is sleeping\n", time, phil->name);
		sem_post(all->sem_prnt);
		ft_usleep(all->sleep_time, time, all->init_time);
	}
	sem_post(all->sem_prnt);
	return (NULL);
}

void	*ft_wait(void *args)
{
	t_main	*main;

	main = (t_main *)args;
	sem_wait(main->all->sem_dth);
	sem_post(main->all->sem_dth);
	main->all->flag = 1;
	return (NULL);
}

int	main(int ac, char **av)
{
	t_all			*all;
	t_phil			*phils;
	int				flag;

	all = NULL;
	phils = NULL;
	if (init_struct(&all))
		return (1);
	all->sem_name = "forks_42";
	all->sem_dth_name = "dth_42";
	all->sem_prnt_name = "prnt_42";
	flag = get_args(ac, av + 1, all);
	flag = init_sem(all, flag);
	flag = init_phils(&phils, all, flag);
	flag = init_forks(phils, all, flag);
	sem_unlink(all->sem_name);
	sem_unlink(all->sem_dth_name);
	free (phils);
	return (0);
}
