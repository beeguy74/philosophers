/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:34:45 by tphung            #+#    #+#             */
/*   Updated: 2021/08/06 18:39:48 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		pthread_detach(threads[i++]);
	}
	free (threads);
	return (0);
}

pid_t	fork_exec(t_phil *phil, t_all *all)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		init_threads(phil, all);
		exit(1);
	}
	return (pid);
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
	waitpid_forall(pids, all);
	free(pids);
	return (0);
}
