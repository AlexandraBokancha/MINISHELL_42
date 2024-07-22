/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_ter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:22:13 by eschussl          #+#    #+#             */
/*   Updated: 2024/01/16 17:06:26 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_zeri(t_printfstruct structure)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < structure.v_width)
	{
		count += ft_putlchar(' ');
		i++;
	}
	return (count);
}

char	*ft_mini(t_printfstruct structure, char *src, int nb)
{
	char	*dest;
	int		i;

	i = 0;
	if ((nb < 0 && !structure.zero) || (nb < 0 && structure.zero \
	&& structure.v_width <= ft_strlen(src)) || (nb < 0 && structure.zero \
	&& structure.precision && structure.v_width >= structure.v_precision))
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 2, ' ');
		if (!dest)
			return (NULL);
		dest[i] = '-';
		i++;
		ft_strdcpy(src, dest + 1, 0);
		return (dest);
	}
	dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
	if (!dest)
		return (NULL);
	ft_strdcpy(src, dest, 0);
	return (dest);
}
