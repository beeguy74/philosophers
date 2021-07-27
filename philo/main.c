/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/27 17:09:18 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time_ms(long long int init_time)
{
	t_timeval	timeval;
	int			elaps_time;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	/*usec = (timeval.tv_usec - init_time->tv_usec);
	elaps_time = (timeval.tv_sec - init_time->tv_sec) * 1000;
	elaps_time += usec / 1000;*/
	elaps_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - init_time;
	return (elaps_time);
}

int	init_struct(t_all **all)
{
	t_timeval 		*init_time;
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
		.must_eat = 0,
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
		(*phils)[i].name = i;
		(*phils)[i].left_fork = i;
		(*phils)[i].actual_eat_time = 0;
		if (i == 0)
		{
			(*phils)[i].right_fork = i;
			(*phils)[i].left_fork = all->numb - 1;
		}
		else
			(*phils)[i].right_fork = i - 1;
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

void	ft_usleep(int time)
{
	int	i;
	int	max;

	i = 0;
	max = time / 100;
	while (i++ < max)
		usleep(100000);
}

void	*eat(void *args)
{
	t_phil			*main;
	long long int	init_time;

	main = (t_phil *)args;
	init_time = main->all->init_time;
	while (1)
	{
		// pthread_mutex_lock(&main.forks[main.all->numb]);
		if (main->all->flag)
			break ;
		printf("%d %d is thinking\n", elapsed_time_ms(init_time), main->name);
		// pthread_mutex_unlock(&main.forks[main.all->numb]);

		pthread_mutex_lock(&main->forks[main->right_fork]);
		pthread_mutex_lock(&main->forks[main->left_fork]);
		main->actual_eat_time = elapsed_time_ms(init_time);

		// pthread_mutex_lock(&main.forks[main.all->numb]);
		if (main->all->flag)
			break ;
		printf("%d %d is eating\n", main->actual_eat_time, main->name);
		// pthread_mutex_unlock(&main.forks[main.all->numb]);

		usleep(main->all->eat_time * 1000);
		//ft_usleep(main.all->eat_time);
		pthread_mutex_unlock(&main->forks[main->left_fork]);
		pthread_mutex_unlock(&main->forks[main->right_fork]);

		// pthread_mutex_lock(&main.forks[main.all->numb]);
		if (main->all->flag)
			break ;
		printf("%d %d is sleeping\n", elapsed_time_ms(init_time), main->name);
		// pthread_mutex_unlock(&main.forks[main.all->numb]);

		usleep(main->all->sleep_time * 1000);
		//ft_usleep(main.all->sleep_time);
	}
	return (NULL);
}

int	peace_death(t_phil main)
{
	int	time_elapsed;
	int	death_time;

	time_elapsed = elapsed_time_ms(main.all->init_time);
	death_time = time_elapsed - main.actual_eat_time;
	if (death_time > main.all->die_time && time_elapsed > death_time)
		return (time_elapsed);
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
	printf("work\n");
	i = 0;
	while (i < main->all->numb)
	{
		if (pthread_create(&threads[i], NULL, eat, &(main[i])))
			return (1);
		i++;
	}
	i = 0;
	while (1)
	{
		main->all->flag = peace_death(main[i]);
		if (main->all->flag)
		{
			printf("%d %d is dead\n", main->all->flag, main[i].name);
			break ;
		}
		if (++i == main->all->numb)
			i = 0;
	}
	i = 0;
	while (i < main->all->numb)
		pthread_join(threads[i++], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_all		*all;
	t_phil		*phils;
	pthread_mutex_t *forks;
	int			flag;

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
