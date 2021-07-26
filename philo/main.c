/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/26 19:02:23 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time_ms(t_timeval *init_time)
{
	t_timeval	timeval;
	int			elaps_time;
	int			usec;

	if (gettimeofday(&timeval, NULL))
		return (-1);
	usec = (timeval.tv_usec - init_time->tv_usec);
	elaps_time = (timeval.tv_sec - init_time->tv_sec) * 1000;
	elaps_time += usec / 1000;
	return (elaps_time);
}

int	init_struct(t_all *all, t_timeval *init_time)
{

	if (gettimeofday(init_time, NULL))
		return (1);
	*all = (t_all){
		.die_time = 0,
		.eat_time = 0,
		.sleep_time = 0,
		.numb = 0,
		.must_eat = 0,
		.init_time = init_time
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
		(*phils)[i].name = i;
		(*phils)[i].left_fork = i;
		if (i == 0)
		{
			(*phils)[i].left_fork = all->numb - 1;
			(*phils)[i].right_fork = i;
		}
		else if (i == all->numb - 1)
		{
			(*phils)[i].left_fork = i - 1;
			(*phils)[i].right_fork = i;
		}
		else
			(*phils)[i].right_fork = i - 1;
		i++;
	}
	return (0);
}

int	init_mutex(pthread_mutex_t **forks, t_all *all, int flag)
{
	int		i;

	if (flag)
		return (1);
	i = 0;
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (all->numb));
	if (!(*forks))
		return (1);
	while (i < all->numb)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	*eat(void *args)
{
	t_main *main;

	main = (t_main *)args;
	while (1)
	{
		//ft_printf("%d started dinner\n", main->phils->name);
		ft_putnbr_fd(main->phils->name, 1);
		ft_putendl_fd(" is thinking", 1);
		pthread_mutex_lock(&main->forks[main->phils->right_fork]);
		pthread_mutex_lock(&main->forks[main->phils->left_fork]);
		ft_putnbr_fd(main->phils->name, 1);
		ft_putendl_fd(" is eating", 1);
		usleep(main->all->eat_time * 1000);
	 
		//ft_printf("%d is eating\n", main->phils->name);
	 
		pthread_mutex_unlock(&main->forks[main->phils->right_fork]);
		pthread_mutex_unlock(&main->forks[main->phils->left_fork]);
		ft_putnbr_fd(main->phils->name, 1);
		ft_putendl_fd(" sleeping", 1);
		usleep(main->all->sleep_time * 1000);
	}
 
    //ft_printf("%d finished dinner\n", main->phils->name);
	return (NULL);
}

int	init_threads(t_main *main, int flag)
{
	int			i;
	pthread_t	*threads;
	t_main		tmp;
	t_phil		*mas;

	if (flag)
		return (1);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (main->all->numb));
	if (!threads)
		return (1);
	i = 0;
	mas = main->phils;
	tmp.forks = main->forks;
	tmp.all = main->all;
	while (i < main->all->numb)
	{
		tmp.phils = &mas[i];
		if (i == main->all->numb - 1)
			usleep(100);
		if (pthread_create(&threads[i], NULL, eat, &tmp))
			return (1);
		i++;
	}
	i = 0;
	while (i < main->all->numb)
		pthread_join(threads[i++], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_timeval	timeval;
	t_all		all;
	t_main		main;
	int			flag;
	int			i;

	if (init_struct(&all, &timeval))
		return (1);
	main.all = &all;
	ft_printf("seconds = %d \n", elapsed_time_ms(all.init_time));

	flag = get_args(ac, av + 1, &all);
	ft_printf("ARGs = %d %d %d %d \n", all.numb, all.die_time, \
			all.eat_time, all.sleep_time);

	i = 0;
	flag = init_phils(&main.phils, &all, flag);
	while (i < all.numb)
	{
		ft_putstr_fd("work\n", 1);
		ft_printf("name = %d, left = %d, right = %d\n", main.phils[i].name, main.phils[i].left_fork, \
			main.phils[i].right_fork);
		i++;
	}
	flag = init_mutex(&main.forks, &all, flag);
	
	flag = init_threads(&main, flag);
	i = 0;
	free (main.phils);	
	return (0);
}
