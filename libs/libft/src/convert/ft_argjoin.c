/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:07 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:53:26 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counttabsize(char **tab)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			count++;
			j++;
		}
		count++;
		i++;
	}
	return (count - 1);
}

char	*ft_argjoin(char **tab, char c)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (tab[i])
		i++;
	res = ft_calloc(ft_counttabsize(tab) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			res[k++] = tab[i][j++];
		i++;
		if (tab[i])
			res[k++] = c;
		else
			res[k] = 0;
	}
	return (res);
}
