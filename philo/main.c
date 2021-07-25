/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:43:45 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 16:35:25 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_timeval timeval;

	if (gettimeofday(&timeval, NULL))
		return (1);
	ft_printf("seconds = %d \n", (int)timeval.tv_sec);
	puts("Press any key to continue ... ");
	getchar();
	ft_printf("seconds = %d \n", (int)timeval.tv_sec);
	return (0);
}