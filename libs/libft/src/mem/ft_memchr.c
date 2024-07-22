/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:29:30 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:11:01 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryblock, int searchChar, size_t size)
{
	const char	*str;
	int			index;

	index = 0;
	str = memoryblock;
	while (index < (int) size)
	{
		if ((unsigned char) str[index] == (unsigned char) searchChar)
			return ((void *) str + index);
		index++;
	}
	return (NULL);
}
