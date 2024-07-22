/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:44 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:34:10 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_nodpars *current)
{
	char	*dir;

	if (current->flags)
		return (printf("%s: %s: invalid option \n", current->builtin,
				current->flags->var), 2);
	else if (current->args && ms_fake_flag(current->args->var))
		return (2);
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		printf("getcwd() error\n");
		if (errno == ERANGE)
			return (printf("Buffer size is too small.\n"), 1);
	}
	else
		printf("%s\n", dir);
	free(dir);
	return (0);
}
