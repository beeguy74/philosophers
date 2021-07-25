/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:59:39 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 13:46:46 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srt;
	unsigned char	*res;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (dst);
	srt = (unsigned char *)src;
	res = (unsigned char *)dst;
	if (srt < res)
	{
		while (len-- > 0)
			res[len] = srt[len];
	}
	else
	{
		while (i < len)
		{
			res[i] = srt[i];
			i++;
		}
	}
	return (dst);
}
