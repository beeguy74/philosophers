/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 15:01:37 by tphung            #+#    #+#             */
/*   Updated: 2021/08/01 15:10:55 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sem(t_all *all, int flag)
{
	int	test;

	test = 0;
	if (flag)
		return (1);
	sem_unlink(all->sem_name);
	all->sem = sem_open(all->sem_name, O_CREAT, 0666, all->numb);
	if (!all->sem)
		return (1);
	sem_unlink(all->sem_dth_name);
	all->sem_dth = sem_open(all->sem_dth_name, O_CREAT, 0666, 0);
	if (!all->sem_dth)
		return (1);
	return (0);
}

int	init_struct(t_all **all)
{
	t_timeval		*init_time;
	long long int	time;

	init_time = malloc(sizeof(t_timeval));
	if (!init_time || gettimeofday(init_time, NULL))
		return (1);
	time = init_time->tv_sec * 1000 + init_time->tv_usec / 1000;
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
		.init_time = time,
		.sem = NULL,
		.sem_name = NULL
	};
	return (0);
}

int	init_phils(t_phil **phils, t_all *all, int flag)
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
		(*phils)[i].name = i + 1;
		(*phils)[i].actual_eat_time = 0;
		(*phils)[i].num_eat = 0;
		i++;
	}
	return (0);
}

int	init_threads(t_phil *phil, t_all *all)
{
	int			i;
	pthread_t	*threads;
	t_main		main;

	main.all = all;
	main.phil = phil;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * 3);
	if (!threads)
		return (1);
	if (pthread_create(&threads[0], NULL, eat, &main))
		return (1);
	if (pthread_create(&threads[1], NULL, ft_wait, &main))
		return (1);
	death_loop(&main);
	i = 0;
	while (i < 3)
		pthread_detach(threads[i++]);
	return (0);
}

int	init_forks(t_phil *main, t_all *all, int flag)
{
	int			i;
	pid_t		*pids;

	if (flag)
		return (1);
	pids = (pid_t *)malloc(sizeof(pid_t) * (all->numb));
	if (!pids)
		return (1);
	i = -1;
	while (++i < all->numb)
	{
		pids[i] = fork_exec(&main[i], all);
	}
	waitpid_forall(pids, all->numb);
	free(pids);
	return (0);
}
