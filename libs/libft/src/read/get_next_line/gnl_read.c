/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:06:45 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:46:16 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_stc_read(t_gnl_struct *stc, int fd, int *error)
{
	char	buffer[GNL_BUFFER_SIZE];
	int		reader;
	char	*strjoined;

	reader = read(fd, &buffer, GNL_BUFFER_SIZE);
	if (reader == -1)
		return (gnl_error(stc, error, "Error in gnl_stc_read : Unread\n"));
	strjoined = malloc(stc->size + reader + 1);
	stc->read = reader;
	if (!strjoined)
		return (gnl_error(stc, error, "Error in gnl_stc_read : Malloc\n"));
	strjoined[stc->size + reader] = '\0';
	while (--reader >= 0)
	{
		strjoined[stc->size + reader] = buffer[reader];
		if (buffer[reader] == '\n')
			stc->nlpos = stc->size + reader;
	}
	reader = -1;
	while (stc->str[++reader])
		strjoined[reader] = stc->str[reader];
	stc->size = stc->read + stc->size;
	free (stc->str);
	stc->str = strjoined;
}

void	gnl_read(t_gnl_struct *stc, int fd, int *error)
{
	while (stc->nlpos == -1 && stc->read == GNL_BUFFER_SIZE)
	{
		gnl_stc_read(stc, fd, error);
		if (*error == -1)
			return ;
	}
}
