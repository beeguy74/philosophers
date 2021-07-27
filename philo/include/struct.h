/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:54:29 by tphung            #+#    #+#             */
/*   Updated: 2021/07/27 16:28:36 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct timeval t_timeval;

typedef struct s_all
{
	int				numb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				flag;
	//t_timeval	*init_time;
	long long int	init_time;
} t_all;

typedef struct s_phil
{
	int				name;
	int				left_fork;
	int				right_fork;
	int				actual_eat_time;
	pthread_mutex_t	*forks;
	struct s_all	*all;
} t_phil;

#endif
