/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeiarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:30:45 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:45:34 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freeiarray(int **tab, int size)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (i < size)
	{
		free (tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
}
