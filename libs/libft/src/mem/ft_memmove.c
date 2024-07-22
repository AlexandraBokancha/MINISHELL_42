/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:55:12 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:03:31 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_functional_memcpy(char *dest, const char *src, int i, int size)
{
	if (i != 0)
	{
		while (i >= 0)
		{
			dest[i] = src[i];
			i--;
		}
		return (dest);
	}
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*tempdest;
	const char	*tempsource;

	if (dest == src)
		return (dest);
	tempdest = dest;
	tempsource = src;
	if (tempsource < tempdest)
	{
		tempdest = ft_functional_memcpy(tempdest, tempsource, size - 1, size);
		return (dest);
	}
	tempdest = ft_functional_memcpy(tempdest, tempsource, 0, size);
	return (dest);
}
