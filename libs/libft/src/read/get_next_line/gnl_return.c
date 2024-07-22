/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:04:19 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:47:35 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_exit(t_gnl_struct *stc)
{
	if (stc->str)
	{
		free (stc->str);
		stc->str = NULL;
	}
	if (stc->str_static)
	{
		free (stc->str_static);
		stc->str_static = NULL;
	}	
}

static void	gnl_str_static(t_gnl_struct *stc, int *error)
{
	int	i;
	int	j;

	if (stc->nlpos == -1 || stc->nlpos == stc->size - 1)
		return (gnl_exit(stc));
	if (stc->str_static)
		free (stc->str_static);
	stc->str_static = malloc (GNL_BUFFER_SIZE + 1);
	if (!stc->str_static)
		return (gnl_error(stc, error, \
			"Error in Gnl_str_static function : Malloc\n"));
	i = stc->nlpos + 1;
	j = 0;
	while (stc->str[i])
		stc->str_static[j++] = stc->str[i++];
	free(stc->str);
	stc->str_static[j] = '\0';
}

static void	gnl_str_return(t_gnl_struct *stc, int *error)
{
	int		i;

	if (stc->size == 0)
		return ;
	if (stc->nlpos != -1)
		stc->str_return = malloc (stc->nlpos + 2);
	else
		stc->str_return = malloc (stc->size + 1);
	if (!stc->str_return)
		return (gnl_error(stc, error, \
			"Error in Gnl_str_return function : Malloc\n"));
	i = -1;
	if (stc->nlpos != -1)
	{
		while (++i <= stc->nlpos)
			stc->str_return[i] = stc->str[i];
	}
	else
	{
		while (stc->str[++i])
			stc->str_return[i] = stc->str[i];
	}
	stc->str_return[i] = '\0';
}

void	gnl_return(t_gnl_struct *stc, int *error)
{
	gnl_str_return(stc, error);
	if (*error == GNL_ERROR)
		return ;
	gnl_str_static(stc, error);
}
