/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/08/09 14:06:14 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_up(t_phil *main, long long int init_time)
{
	ft_mut_print(main, "is thinking", init_time, main->name);
	if (main->name % 2 == 0 && main->num_eat == 0)
		usleep(1400);
	pthread_mutex_lock(&main->forks[main->right_fork]);
	ft_mut_print(main, "has taken right fork", init_time, main->name);
	pthread_mutex_lock(&main->forks[main->left_fork]);
	ft_mut_print(main, "has taken left fork", init_time, main->name);
}

void	forks_down(t_phil *main)
{
	pthread_mutex_unlock(&main->forks[main->left_fork]);
	pthread_mutex_unlock(&main->forks[main->right_fork]);
}

void	*eat(void *args)
{
	t_phil			*main;
	int				asleep_time;
	long long int	init_time;

	main = (t_phil *)args;
	init_time = main->all->init_time;
	while (main->num_eat != main->all->must_eat)
	{
		if (!main->all->flag && main->num_eat != main->all->must_eat)
			forks_up(main, init_time);
		main->actual_eat_time = elapsed_time_ms(init_time);
		if (!main->all->flag && main->num_eat != main->all->must_eat)
			ft_mut_print(main, "is eating", init_time, main->name);
		ft_usleep(main->all->eat_time, main->actual_eat_time, init_time);
		main->num_eat++;
		forks_down(main);
		asleep_time = elapsed_time_ms(init_time);
		if (!main->all->flag && main->num_eat != main->all->must_eat)
			ft_mut_print(main, "is sleeping", init_time, main->name);
		ft_usleep(main->all->sleep_time, asleep_time, init_time);
	}
	return (NULL);
}

int	init_threads(t_phil *main, int flag)
{
	int			i;
	pthread_t	*threads;

	if (flag)
		return (1);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (main->all->numb));
	if (!threads)
		return (1);
	i = -1;
	while (++i < main->all->numb)
	{
		if (pthread_create(&threads[i], NULL, eat, &(main[i])))
			return (1);
	}
	death_loop(&main);
	i = 0;
	while (i < main->all->numb)
	{
		if (main->all->flag)
			pthread_detach(threads[i++]);
		else
			pthread_join(threads[i++], NULL);
	}
	free (threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_all			*all;
	t_phil			*phils;
	pthread_mutex_t	*forks;
	int				flag;

	all = NULL;
	phils = NULL;
	forks = NULL;
	if (init_struct(&all))
		return (1);
	flag = get_args(ac, av + 1, all);
	flag = init_mutex(&forks, all, flag);
	flag = init_phils(&phils, all, forks, flag);
	flag = init_threads(phils, flag);
	free (forks);
	free (all);
	free (phils);
	all = NULL;
	phils = NULL;
	forks = NULL;
	return (0);
}
