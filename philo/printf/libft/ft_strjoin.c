/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:22:19 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 13:22:10 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	dest_size;

	if (!s1 || !s2)
		return (NULL);
	dest_size = (1 + ft_strlen((char *)s1) + ft_strlen((char *)s2));
	dest = ft_calloc(dest_size, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, dest_size);
	ft_strlcat(dest, s2, dest_size);
	return (dest);
}
