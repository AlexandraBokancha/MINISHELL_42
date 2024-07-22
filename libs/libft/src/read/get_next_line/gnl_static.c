/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:07:38 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:46:48 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_stc_static(t_gnl_struct *stc, int *error)
{
	int				i;

	stc->str = malloc(GNL_BUFFER_SIZE + 1);
	if (!stc->str)
		return (gnl_error(stc, error, "Error in gnl_str_static : Malloc\n"));
	i = 0;
	stc->nlpos = -1;
	while (stc->str_static[i])
	{
		stc->str[i] = stc->str_static[i];
		if (stc->nlpos == -1 && stc->str[i] == '\n')
			stc->nlpos = i;
		i++;
	}
	stc->read = GNL_BUFFER_SIZE;
	stc->size = i;
	stc->str[i] = '\0';
}

static void	gnl_stc_no_static(t_gnl_struct *stc, int fd, int *error)
{
	char	buffer[GNL_BUFFER_SIZE];
	int		reader;

	stc->str = malloc (GNL_BUFFER_SIZE + 1);
	if (!stc->str)
		return (gnl_error(stc, error, "Error in gnl_stc_no_static : Malloc\n"));
	reader = read(fd, &buffer, GNL_BUFFER_SIZE);
	if (stc->read == -1)
		return (gnl_error(stc, error, "Error in gnl_stc_no_static : Unread\n"));
	stc->str[reader] = '\0';
	stc->size = reader;
	stc->read = reader;
	stc->nlpos = -1;
	while (--reader >= 0)
	{
		stc->str[reader] = buffer[reader];
		if (stc->str[reader] == '\n')
			stc->nlpos = reader;
	}
}

void	gnl_static(t_gnl_struct *stc, int fd, int *error)
{
	if (stc->str_static)
		gnl_stc_static(stc, error);
	else
		gnl_stc_no_static(stc, fd, error);
}
