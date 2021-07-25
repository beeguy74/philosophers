/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:56:06 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 13:21:48 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		dest_len;
	const char	*begin_src;
	const char	*begin_dst;

	i = dstsize;
	begin_src = src;
	begin_dst = dst;
	while (i-- != 0 && *dst != '\0')
		dst++;
	dest_len = dst - begin_dst;
	i = dstsize - dest_len;
	if (i-- == 0)
		return (dest_len + ft_strlen((char *)src));
	while (*src != '\0')
	{
		if (i != 0)
		{
			*dst++ = *src;
			i--;
		}
		src++;
	}
	*dst = '\0';
	return (dest_len + (src - begin_src));
}
