/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:21:27 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:23:49 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_env_elem(t_main *main, char *elem)
{
	t_nodenv	*tmp;

	tmp = main->envp.head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, elem, ft_strlen(elem)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ms_env(t_main *main, t_nodpars *current)
{
	t_nodenv	*tmp;

	if (current->flags || current->args)
	{
		if (current->flags)
			return (printf("%s: %s: invalid option \n", current->builtin,
					current->flags->var), 125);
		else if (current->args->var)
			return (printf("No arguments allowed for env. \
				Look at mini-shell subject :)\n"), 1);
	}
	tmp = main->envp.head;
	while (tmp)
	{
		if (!tmp->exp)
			printf("%s=%s \n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
