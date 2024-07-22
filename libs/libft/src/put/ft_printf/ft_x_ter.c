/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_ter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:32:03 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/21 15:16:02 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strxbis(t_printfstruct structure, \
	char *prefix, char *src, char *dest)
{
	int	i;
	int	j;

	if (structure.zero && !structure.precision)
	{
		ft_strdcpy(prefix, dest, 0);
	}
	i = ft_strlen(src) - 1;
	j = ft_strlen(dest) - 1;
	while (i >= 0)
		dest[j--] = src[i--];
	if (!(structure.zero && !structure.precision))
	{
		i = ft_strlen(prefix) - 1;
		while (i >= 0)
			dest[j--] = prefix[i--];
	}
	return (dest);
}
