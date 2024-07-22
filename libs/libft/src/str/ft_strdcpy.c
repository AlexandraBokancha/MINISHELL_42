/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:52:46 by eschussl          #+#    #+#             */
/*   Updated: 2023/12/15 15:33:29 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strdcpy(char *src, char *dest, int dif)
{
	int	i;
	int	j;

	if (dif >= 0)
	{
		i = 0;
		while (src[i] && dest[i + dif])
		{
			dest[i + dif] = src[i];
			i++;
		}
	}
	else
	{
		i = ft_strlen(src) - 1;
		j = ft_strlen(dest) + dif - 1;
		while (i >= 0 && j >= 0)
			dest[j--] = src[i--];
	}
	return (dest);
}
