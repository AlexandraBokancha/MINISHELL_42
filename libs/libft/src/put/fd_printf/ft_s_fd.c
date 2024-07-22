/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:50:43 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/08 16:02:53 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_prec(t_printfstruct structure, char *src)
{
	char	*dest;

	dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
	if (!dest)
		return (NULL);
	ft_strdcpy(src, dest, 0);
	if (structure.precision)
	{
		if (structure.v_precision < ft_strlen(dest))
			dest[structure.v_precision] = '\0';
	}
	return (dest);
}

static char	*ft_minus(t_printfstruct structure, char *dest, char *src)
{
	int	i;
	int	j;

	if (structure.minus)
	{
		i = 0;
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		return (dest);
	}
	i = ft_strlen(dest)- 1;
	j = ft_strlen(src) - 1;
	while (j >= 0)
	{
		dest[i] = src[j];
		i--;
		j--;
	}
	return (dest);
}

static char	*ft_width(t_printfstruct structure, char *src)
{
	char	*dest;

	if (structure.v_width > ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), structure.v_width + 1, ' ');
		if (!dest)
			return (NULL);
	}
	else
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
		if (!dest)
			return (NULL);
	}
	dest = ft_minus(structure, dest, src);
	if (!dest)
		return (NULL);
	return (dest);
}

int	ft_s_fd(t_printfstruct structure, char *s, int fd)
{
	int		count;
	char	*tmp;
	char	*tmp2;

	if (structure.v_precision < 6 && structure.precision && !s)
		return (0);
	else if (!s)
		return (ft_s_fd(structure, "(null)", fd));
	tmp = ft_prec(structure, s);
	if (!tmp)
		return (0);
	tmp2 = ft_width(structure, tmp);
	free (tmp);
	if (!tmp2)
		return (0);
	count = ft_putlstr_fd(tmp2, ft_strlen(tmp2), fd);
	free (tmp2);
	return (count);
}
