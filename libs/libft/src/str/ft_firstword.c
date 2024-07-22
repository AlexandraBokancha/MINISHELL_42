/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_firstword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:56:04 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:46:50 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_firstword(char *str, char c)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[j] && str[j] == c)
		j++;
	while (str[i + j] && str[i + j] != c)
		i++;
	res = ft_calloc(sizeof(char), (i + 1));
	if (!res)
		return (NULL);
	i = j;
	while (str[i] && str[i] != c)
	{
		res[i - j] = str[i];
		i++;
	}
	return (res);
}
