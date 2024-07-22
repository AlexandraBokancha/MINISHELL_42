/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gwf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:56:01 by eschussl          #+#    #+#             */
/*   Updated: 2024/03/10 16:31:21 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gwf_strjoin(char *heap, char *stack)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	if (!heap || !heap[0])
	{
		res = malloc (ft_strlen(stack) + 1);
		while (stack[++i])
			res[i] = stack[i];
		res[i] = 0;
		return (res);
	}
	res = malloc ((ft_strlen(stack) + ft_strlen(heap) + 1) * sizeof(char));
	while (heap[++i])
		res[i] = heap[i];
	j = -1;
	while (stack[++j])
		res[i + j] = stack[j];
	res[i + j] = 0;
	free (heap);
	return (res);
}

char	*gwf(int fd)
{
	static char	*res = NULL;
	char		buffer[GWF_BUFFER_SIZE + 1];
	int			reader;

	if (fd == -1 && res)
		return (free (res), NULL);
	else if (fd == -1)
		return (NULL);
	reader = read(fd, &buffer, GWF_BUFFER_SIZE);
	if (reader <= 0)
		return (fd_printf(2, "Error : Nothing to read in function gwf\n"), NULL);
	while (buffer[0])
	{
		buffer[reader] = 0;
		res = gwf_strjoin(res, buffer);
		if (!res)
			return (NULL);
		reader = read(fd, &buffer, GWF_BUFFER_SIZE);
	}
	res = gwf_strjoin(res, buffer);
	return (res);
}
