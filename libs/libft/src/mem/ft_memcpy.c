/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:17:48 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:11:06 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*str;
	char		*str2;

	if (dest == src)
		return (dest);
	i = 0;
	str = src;
	str2 = dest;
	while (i < n)
	{
		str2[i] = str[i];
		i++;
	}
	return (dest);
}
