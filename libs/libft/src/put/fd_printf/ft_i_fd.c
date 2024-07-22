/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:19:58 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/07 15:32:51 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_int(long n)
{
	int	count;

	count = 1;
	if (n < 0)
		n = -n;
	while (n / 10)
	{
		n = n / 10;
		count++;
	}	
	return (count);
}

static char	*ft_itoaprintf(int n)
{
	char	*str;
	int		size;
	long	x;

	x = (long) n;
	size = ft_size_int(x);
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (x < 0)
		x = -x;
	while (size--)
	{
		if (str[size] == '-')
			break ;
		str[size] = x % 10 + '0';
		x = x / 10;
	}
	return (str);
}

static t_printfstruct	ft_struc_plus_space(t_printfstruct structure)
{
	if (structure.minus || structure.space)
		structure.v_width++;
	return (structure);
}

static char	*ft_prec(t_printfstruct structure, char *src)
{
	char	*dest;
	int		i;
	int		j;

	if (structure.plus || structure.space)
		structure = ft_struc_plus_space(structure);
	if (!structure.precision || structure.v_precision <= ft_strlen(src))
	{
		dest = ft_setalloc(sizeof(char), ft_strlen(src) + 1, ' ');
		if (!dest)
			return (NULL);
	}
	else
	{
		dest = ft_setalloc(sizeof(char), structure.v_precision + 1, '0');
		if (!dest)
			return (NULL);
	}
	i = ft_strlen(dest) - 1;
	j = ft_strlen(src) - 1;
	while (j >= 0)
		dest[i--] = src[j--];
	return (dest);
}

int	ft_i_fd(t_printfstruct structure, int nb, int fd)
{
	int		count;
	char	*str;
	char	*str2;

	if (!nb && structure.precision && !structure.v_precision)
		return (ft_zeri_fd(structure, fd));
	str = ft_itoaprintf(nb);
	if (!str)
		return (0);
	str2 = ft_prec(structure, str);
	free (str);
	if (!str2)
		return (0);
	str = ft_ibis(structure, nb, str2);
	if (!str)
		return (0);
	count = ft_putlstr_fd(str, ft_strlen(str), fd);
	free (str);
	return (count);
}
