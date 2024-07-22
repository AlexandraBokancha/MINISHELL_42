/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:12:16 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:01:34 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
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
