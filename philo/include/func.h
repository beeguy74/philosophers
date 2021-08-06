/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:40:01 by tphung            #+#    #+#             */
/*   Updated: 2021/08/06 17:03:07 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

int		get_args(int argc, char **argv, t_all *all);
int		elapsed_time_ms(long long int init_time);
void	ft_usleep(int time, int when_asleep, long long int init_time);
void	ft_mut_print(t_phil *main, char *mes, long long int time, int name);
int		death_loop(t_phil **main);
int		init_struct(t_all **all);
int		init_mutex(pthread_mutex_t **forks, t_all *all, int flag);
int		init_phils(t_phil **phil, t_all *all, pthread_mutex_t *fork, int flag);

#endif