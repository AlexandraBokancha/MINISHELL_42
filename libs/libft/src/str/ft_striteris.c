/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteris.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:02:38 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:46:09 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_striteris(const char *str, int (is)(int))
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
