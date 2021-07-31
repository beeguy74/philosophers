/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:54:29 by tphung            #+#    #+#             */
/*   Updated: 2021/07/31 18:36:53 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct timeval t_timeval;

typedef struct	s_all
{
	int				numb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				flag;
	long long int	init_time;
	char 			*sem_name;
	char 			*sem_dth_name;
	sem_t			*sem_dth;
	sem_t			*sem;
} t_all;

typedef struct	s_phil
{
	int				name;
	int				actual_eat_time;
	int				num_eat;
	int				stop_eat;
} t_phil;

typedef struct	s_main
{
	t_phil	*phil;
	t_all	*all;
} t_main;

#endif
