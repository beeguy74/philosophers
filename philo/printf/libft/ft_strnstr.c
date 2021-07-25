/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:21:25 by tphung            #+#    #+#             */
/*   Updated: 2021/07/25 13:20:35 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[j] != '\0' && j < len)
	{
		if (haystack[j] == needle[i])
		{
			j++;
			i++;
		}
		else if (i > 0)
			i = 0;
		else
			j++;
		if (needle[i] == '\0')
			return ((char *)haystack + j - i);
	}
	return (NULL);
}
