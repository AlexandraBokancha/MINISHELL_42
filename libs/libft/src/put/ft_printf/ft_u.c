/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:12:48 by eschussl          #+#    #+#             */
/*   Updated: 2024/01/16 17:08:39 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_zeru(t_printfstruct structure)
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

static int	ft_size_int(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count ++;
		n = -n;
	}
	while (n / 10)
	{
		n = n / 10;
		count++;
	}	
	return (count);
}

static char	*ft_itoa_u(unsigned int n)
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
	{
		str[0] = '-';
		x = -x;
	}
	while (size--)
	{
		if (str[size] == '-')
			break ;
		str[size] = x % 10 + '0';
		x = x / 10;
	}
	return (str);
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
		dest = ft_setalloc(sizeof(char), structure.v_precision + 1, '0');
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

int	ft_u(t_printfstruct structure, unsigned int nb)
{
	char	*str;
	int		count;
	char	*str2;

	if (!nb && structure.precision && !structure.v_precision)
		return (ft_zeru(structure));
	str = ft_itoa_u(nb);
	if (!str)
		return (0);
	str2 = ft_prec(structure, str);
	free (str);
	if (!str2)
		return (0);
	str = ft_widthu(structure, str2);
	free (str2);
	if (!str)
		return (0);
	count = ft_putlstr(str, ft_strlen(str));
	free (str);
	return (count);
}
