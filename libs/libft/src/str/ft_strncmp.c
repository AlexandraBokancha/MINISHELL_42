/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:25:43 by eschussl          #+#    #+#             */
/*   Updated: 2024/03/10 16:23:52 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if ((unsigned char)first[i] != (unsigned char)second[i])
			return ((unsigned char) first[i] - (unsigned char) second[i]);
		if ((unsigned char) !first[i] || (unsigned char) !second[i])
			return ((unsigned char) first[i] - (unsigned char) second[i]);
		i++;
	}
	return (0);
}
