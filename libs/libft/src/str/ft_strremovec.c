/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremovec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:26:18 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:45:58 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countchar(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_strremovec(char *str, char c)
{
	char	*res;
	int		i;
	int		j;

	res = ft_calloc(ft_countchar(str, ' ') + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			res[j++] = str[i];
		i++;
	}
	return (res);
}
