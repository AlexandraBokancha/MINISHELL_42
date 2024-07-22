/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:53:19 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:05:52 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s2[0])
		return ((char *)s1);
	while (i < len && s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && i + j < len)
		{
			j++;
			if (!(s2[j]))
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
