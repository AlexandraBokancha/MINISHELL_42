/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:18:57 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/21 15:14:13 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_plus_space_bis(char *src)
{
	char	*dest;

	dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
	if (!dest)
		return (NULL);
	ft_strdcpy(src, dest, 0);
	return (dest);
}

static char	*ft_plus_space(t_printfstruct structure, char *src, int nb)
{
	char	*dest;

	if (nb >= 0 && (structure.plus || structure.space))
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 2, ' ');
		if (!dest)
			return (NULL);
		if (structure.plus)
			dest[0] = '+';
		else if (structure.space)
			dest[0] = ' ';
		ft_strdcpy(src, dest + 1, 0);
		return (dest);
	}
	dest = ft_plus_space_bis(src);
	if (!dest)
		return (NULL);
	return (dest);
}

static char	*ft_strp(t_printfstruct structure, char *src, char *dest)
{
	int	i;
	int	j;

	if (structure.minus)
	{
		j = 0;
		while (src[j])
		{
			dest[j] = src[j];
			j++;
		}
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

static char	*ft_width(t_printfstruct structure, char *src, int nb)
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
		dest = ft_calloc(sizeof(char), structure.v_width + 1);
		if (!dest)
			return (NULL);
		if (structure.zero && !structure.precision && !structure.minus)
		{
			ft_memset(dest, '0', structure.v_width);
			if (nb < 0)
				dest[0] = '-';
		}
		else
			ft_memset(dest, ' ', structure.v_width);
	}
	dest = ft_strp(structure, src, dest);
	return (dest);
}

char	*ft_ibis(t_printfstruct structure, int nb, char *str)
{
	char	*str2;

	str2 = ft_mini(structure, str, nb);
	free (str);
	if (!str2)
		return (NULL);
	str = ft_plus_space(structure, str2, nb);
	free(str2);
	if (!str)
		return (NULL);
	str2 = ft_width(structure, str, nb);
	if (!str2)
		return (NULL);
	free (str);
	return (str2);
}
