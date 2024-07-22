/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:07:11 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 18:10:16 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_var(t_nodargs *head)
{
	void	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->var)
			free(head->var);
		if (head)
			free(head);
		head = tmp;
	}
}

void	ms_free_envp(t_main *main)
{
	void	*tmp;

	while (main->envp.head)
	{
		tmp = main->envp.head->next;
		if (main->envp.head->name)
			free(main->envp.head->name);
		if (!main->envp.head->exp)
			free(main->envp.head->value);
		free(main->envp.head);
		main->envp.head = tmp;
	}
}
