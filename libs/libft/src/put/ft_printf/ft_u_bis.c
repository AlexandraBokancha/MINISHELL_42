/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:04:10 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/21 15:16:15 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strp(t_printfstruct structure, char *src, char *dest)
{
	int	i;
	int	j;

	if (structure.minus)
	{
		ft_strdcpy(src, dest, 0);
	}
	else
	{
		i = ft_strlen(src) - 1;
		j = ft_strlen(dest) - 1;
		while (i >= 0)
			dest[j--] = src[i--];
	}
	return (dest);
}

static char	*ft_widthbis(t_printfstruct structure)
{
	char	*dest;

	if (structure.zero && !structure.precision && !structure.minus)
	{
		dest = ft_setalloc(sizeof(char), structure.v_width + 1, '0');
		if (!dest)
			return (NULL);
	}
	else
	{
		dest = ft_setalloc(sizeof(char), structure.v_width + 1, ' ');
		if (!dest)
			return (NULL);
	}
	return (dest);
}

char	*ft_widthu(t_printfstruct structure, char *src)
{
	char	*dest;

	if (structure.v_width <= ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
		if (!dest)
			return (NULL);
	}
	else
	{
		dest = ft_widthbis(structure);
		if (!dest)
			return (NULL);
	}
	dest = ft_strp(structure, src, dest);
	if (!dest)
		return (NULL);
	return (dest);
}
