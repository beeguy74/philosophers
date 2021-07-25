/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_content_numb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:10:50 by tphung            #+#    #+#             */
/*   Updated: 2021/07/21 20:34:45 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_numb(t_list *lst, int numb)
{
	int		i;
	t_list	*res;

	i = 0;
	res = 0;
	if (lst)
	{
		while (lst->next && i++ < numb)
			lst = lst->next;
		res = lst;
	}
	return (res);
}
