/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:28:08 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/19 15:10:48 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	destlen = ft_strlen(dst);
	if (size <= destlen)
		return (size + srclen);
	i = 0;
	while (src[i] && destlen + i < size - 1)
	{
		dst[i + destlen] = src[i];
		i++;
	}
	dst[i + destlen] = '\0';
	if (size < destlen)
		return (size + srclen);
	else
		return (srclen + destlen);
}
