/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:29:02 by eschussl          #+#    #+#             */
/*   Updated: 2024/03/10 17:50:53 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_prec(t_printfstruct structure, char *src)
{
	char	*dest;
	int		i;
	int		j;

	if (structure.v_precision > ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), structure.v_precision + 1, '0');
		if (!dest)
			return (NULL);
		i = ft_strlen(src) - 1;
		j = ft_strlen(dest) - 1;
		while (i >= 0)
			dest[j--] = src[i--];
	}
	else
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, '0');
		if (!dest)
			return (NULL);
		ft_strdcpy(src, dest, 0);
	}
	return (dest);
}

static char	*ft_prefix(t_printfstruct structure)
{
	char	*dest;

	if (structure.hash)
	{
		dest = ft_setalloc(sizeof(char), 3, ' ');
		if (!dest)
			return (NULL);
		dest[0] = '0';
		dest[1] = 'x';
	}
	else
	{
		dest = ft_setalloc(sizeof(char), 1, 0);
		if (!dest)
			return (NULL);
	}
	return (dest);
}

static char	*ft_strx(t_printfstruct structure, \
	char *prefix, char *src, char *dest)
{
	int	i;
	int	j;

	if (structure.minus)
	{
		i = 0;
		while (prefix[i])
		{
			dest[i] = prefix[i];
			i++;
		}
		j = 0;
		while (src[j])
		{
			dest[i + j] = src[j];
			j++;
		}
	}
	else
	{
		dest = ft_strxbis(structure, prefix, src, dest);
		if (!dest)
			return (NULL);
	}
	return (dest);
}

static char	*ft_width(t_printfstruct structure, char *prefix, char *src)
{
	char	*dest;

	if (structure.v_width <= ft_strlen(prefix) + ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), \
		ft_strlen(prefix) + ft_strlen(src) + 1, ' ');
	}
	else
	{
		if (structure.zero && !structure.precision && !structure.minus)
			dest = ft_setalloc(sizeof(char), structure.v_width + 1, '0');
		else
			dest = ft_setalloc(sizeof(char), structure.v_width + 1, ' ');
		if (!dest)
			return (NULL);
	}
	dest = ft_strx(structure, prefix, src, dest);
	if (!dest)
		return (NULL);
	return (dest);
}

char	*ft_xbis(t_printfstruct structure, char *str)
{
	char	*prefix;
	char	*str2;

	str2 = ft_prec(structure, str);
	free(str);
	if (!str2)
		return (NULL);
	prefix = ft_prefix(structure);
	if (!prefix)
	{
		free (str2);
		return (NULL);
	}
	str = ft_width(structure, prefix, str2);
	free(str2);
	free(prefix);
	if (!str)
		return (NULL);
	if (structure.specifier == 'X')
		str = ft_strtoupper(str);
	return (str);
}
