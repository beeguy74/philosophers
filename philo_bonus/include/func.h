/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:40:01 by tphung            #+#    #+#             */
/*   Updated: 2021/08/02 18:17:17 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

int		get_args(int argc, char **argv, t_all *all);
void	*eat(void *args);
void	*ft_wait(void *args);
void	*death_loop(void *args);
pid_t	fork_exec(t_phil *phil, t_all *all);
int		waitpid_forall(pid_t *pids, t_all *all);
int		elapsed_time_ms(long long int init_time);
void	ft_usleep(int time, int when_asleep, long long int init_time);
int		init_sem(t_all *all, int flag);
int		init_struct(t_all **all);
int		init_phils(t_phil **phils, t_all *all, int flag);
int		init_threads(t_phil *phil, t_all *all);
int		init_forks(t_phil *main, t_all *all, int flag);

#endif
