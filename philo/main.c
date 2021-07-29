/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/29 16:55:34 by tphung           ###   ########.fr       */
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
		.init_time = time
	};
	return (0);
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
		(*phils)[i].forks = forks;
		(*phils)[i].all = all;
		(*phils)[i].name = i + 1;
		(*phils)[i].left_fork = i;
		(*phils)[i].actual_eat_time = 0;
		(*phils)[i].num_eat = 0;
		if (i == all->numb - 1)
		{
			(*phils)[i].right_fork = i;
			(*phils)[i].left_fork = 0;
		}
		else
			(*phils)[i].right_fork = i + 1;
		i++;
	}
	return (0);
}

int	init_mutex(pthread_mutex_t **forks, t_all *all, int flag)
{
	pthread_mutex_t	*fork;
	int				i;

	if (flag)
		return (1);
	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (all->numb + 1));
	if (!fork)
		return (1);
	while (i < all->numb + 1)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (1);
		i++;
	}
	*forks = fork;
	return (0);
}

void	ft_usleep(int time, int when_asleep, long long int init_time)
{
	while (time > elapsed_time_ms(init_time) - when_asleep)
		usleep(50);
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
		if (main->all->flag)
			break ;
		printf("%-7d %d is thinking\n", elapsed_time_ms(init_time), main->name);
		pthread_mutex_lock(&main->forks[main->left_fork]);
		pthread_mutex_lock(&main->forks[main->right_fork]);
		main->actual_eat_time = elapsed_time_ms(init_time);
		if (main->all->flag)
			break ;
		printf("%-7d %d is eating\n", main->actual_eat_time, main->name);
		ft_usleep(main->all->eat_time, main->actual_eat_time, init_time);
		main->num_eat++;
		pthread_mutex_unlock(&main->forks[main->right_fork]);
		pthread_mutex_unlock(&main->forks[main->left_fork]);
		if (main->all->flag)
			break ;
		asleep_time = elapsed_time_ms(init_time);
		printf("%-7d %d is sleeping\n", asleep_time, main->name);
		ft_usleep(main->all->sleep_time, asleep_time, init_time);
	}
	return (NULL);
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
	printf("%-7d %d is dead\n", (*main)->all->flag, (*main)[i].name);
	return (0);
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
	free (phils);
	return (0);
}
