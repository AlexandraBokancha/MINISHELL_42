/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:00:20 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:45:55 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_error(t_gnl_struct *stc, int *error, char *emessage)
{
	fd_printf(2, "%s", emessage);
	*error = GNL_ERROR;
	if (stc->str)
	{
		free (stc->str);
		stc->str = NULL;
	}
	if (stc->str_return)
	{
		free (stc->str_return);
		stc->str_return = NULL;
	}
	if (stc->str_static)
	{
		free (stc->str_static);
		stc->str_static = NULL;
	}
}

static void	gnl_stc_reini(t_gnl_struct *stc)
{
	stc->nlpos = 0;
	stc->read = 0;
	stc->size = 0;
	stc->str = NULL;
	stc->str_return = NULL;
}

char	*gnl(int fd, int *error)
{
	static t_gnl_struct	stc;

	if (GNL_BUFFER_SIZE < 1 || fd < GNL_ERROR || (fd > GNL_ERROR && fd < 0))
		gnl(GNL_ERROR, error);
	gnl_stc_reini(&stc);
	if (fd == GNL_ERROR && stc.str_static)
		return (gnl_error(&stc, error, ""), NULL);
	else if (fd == GNL_ERROR)
		return (NULL);
	gnl_static(&stc, fd, error);
	if (*error == GNL_ERROR)
		return (NULL);
	gnl_read(&stc, fd, error);
	if (*error == GNL_ERROR)
		return (NULL);
	gnl_return(&stc, error);
	if (*error == GNL_ERROR)
		return (NULL);
	return (stc.str_return);
}
