/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/31 16:50:20 by tphung           ###   ########.fr       */
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

void	ft_usleep(int time, int when_asleep, long long int init_time)
{
	while (time > elapsed_time_ms(init_time) - when_asleep)
		usleep(50);
}

void	eat(t_phil *phil, t_all *all)
{
	int				asleep_time;
	long long int	init_time;

	init_time = all->init_time;
	while (phil->num_eat != all->must_eat)
	{
		/*if (main->all->flag)
			break ;*/
		printf("%-7d %d is thinking\n", elapsed_time_ms(init_time), phil->name);
		sem_wait(all->sem);
		sem_wait(all->sem);
		phil->actual_eat_time = elapsed_time_ms(init_time);
		/*if (main->all->flag)
			break ;*/
		printf("%-7d %d is eating\n", phil->actual_eat_time, phil->name);
		ft_usleep(all->eat_time, phil->actual_eat_time, init_time);
		phil->num_eat++;
		sem_post(all->sem);
		sem_post(all->sem);
		/*if (main->all->flag)
			break ;*/
		asleep_time = elapsed_time_ms(init_time);
		printf("%-7d %d is sleeping\n", asleep_time, phil->name);
		ft_usleep(all->eat_time, phil->actual_eat_time, init_time);
	}
}

/*int	peace_death(t_phil main)
{
	int	time_elapsed;
	int	death_time;

	time_elapsed = elapsed_time_ms(main.all->init_time);
	death_time = time_elapsed - main.actual_eat_time;
	if (death_time - main.all->die_time > 0)
		return (time_elapsed);
	return (0);
}*/

/*int	death_loop(t_phil **main)
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
}*/

pid_t	fork_exec(t_phil *phil, t_all *all)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		/*signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);*/
		all->sem = sem_open(all->sem_name, 0);
		if (!all->sem)
			exit(1);
		eat(phil, all);
		sem_close(all->sem);
		exit(0);
	}
	return (pid);
}

int	waitpid_forall(pid_t *pids, int num)
{
	int	i;
	int	stat;

	i = 0;
	while (i < num)
	{
		waitpid(pids[i], &stat, 0);
		stat = WEXITSTATUS(stat);
		i++;
	}
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
	//death_loop(&main);
	waitpid_forall(pids, all->numb);
	free(pids);
	return (0);
}

int	init_sem(t_all *all, int flag)
{
	if (flag)
		return (1);
	sem_unlink(all->sem_name);
	all->sem = sem_open(all->sem_name, O_CREAT, O_RDWR, all->numb);
	if (!all->sem)
		return (1);
	return (0);
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
	all->sem_name = "/forks_42";
	flag = get_args(ac, av + 1, all);
	flag = init_sem(all, flag);
	flag = init_phils(&phils, all, flag);
	flag = init_forks(phils, all, flag);
	sem_unlink(all->sem_name);
	free (phils);
	return (0);
}
