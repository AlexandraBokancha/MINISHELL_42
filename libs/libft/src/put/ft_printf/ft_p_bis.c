/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:59:14 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/20 14:29:07 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strpbis(t_printfstruct structure, \
	char *prefix, char *src, char *dest)
{
	int	i;
	int	j;

	if (structure.zero && !structure.precision)
	{
		i = 0;
		while (prefix[i])
		{
			dest[i] = prefix[i];
			i++;
		}
	}
	i = ft_strlen(src) - 1;
	j = ft_strlen(dest) - 1;
	while (i >= 0)
		dest[j--] = src[i--];
	i = ft_strlen(prefix) - 1;
	while (i >= 0)
		dest[j--] = prefix[i--];
	return (dest);
}

static char	*ft_strp(t_printfstruct structure, \
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
		dest = ft_strpbis(structure, prefix, src, dest);
		if (!dest)
			return (NULL);
	}
	return (dest);
}

static char	*ft_prec(t_printfstruct structure, char *src)
{
	char	*dest;
	int		i;
	int		j;

	if (!structure.precision || structure.v_precision <= ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
		if (!dest)
			return (NULL);
	}
	else
	{
		dest = ft_setalloc(sizeof(char), structure.v_precision + 1, 0);
		if (!dest)
			return (NULL);
	}
	i = ft_strlen(dest) - 1;
	j = ft_strlen(src) - 1;
	while (j >= 0)
	{
		dest[i] = src[j];
		i--;
		j--;
	}
	return (dest);
}

static char	*ft_width(t_printfstruct structure, char *prefix, char *src)
{
	char	*dest;

	if (structure.v_width <= ft_strlen(prefix) + ft_strlen(src))
		dest = ft_setalloc(sizeof(char), ft_strlen(prefix) \
		+ ft_strlen(src) + 1, ' ');
	else
	{
		if (structure.zero && !structure.precision && !structure.minus)
			dest = ft_setalloc(sizeof(char), structure.v_width + 1, '0');
		else
			dest = ft_setalloc(sizeof(char), structure.v_width + 1, ' ');
	}
	if (!dest)
		return (NULL);
	dest = ft_strp(structure, prefix, src, dest);
	if (!dest)
		return (NULL);
	return (dest);
}

char	*ft_pbis(t_printfstruct structure, char *str, char *prefix)
{
	char	*str2;

	str2 = ft_prec(structure, str);
	if (!str2)
		return (NULL);
	free (str);
	str = ft_width(structure, prefix, str2);
	if (!str)
		return (NULL);
	free (prefix);
	free (str2);
	return (str);
}
