/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:21:04 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/25 18:09:42 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementcount, size_t elementsize)
{
	char	*str;
	size_t	total;

	total = elementcount * elementsize;
	if (elementcount != 0 && total / elementcount != elementsize)
		return (NULL);
	str = malloc(total);
	if (!str)
		return (fd_printf(2, "Error\n"), NULL);
	ft_memset((void *) str, 0, total);
	return ((void *) str);
}
