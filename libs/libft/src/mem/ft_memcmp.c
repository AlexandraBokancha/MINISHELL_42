/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:03:48 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:03:05 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)ptr1)[i] != ((unsigned char *)ptr2)[i])
			return (((unsigned char *)ptr1)[i] - ((unsigned char *)ptr2)[i]);
		i++;
	}
	return (0);
}
