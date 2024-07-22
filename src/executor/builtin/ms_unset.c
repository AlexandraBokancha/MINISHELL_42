/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:34:19 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:44:08 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_free_var2(t_main *main, t_nodenv *tmp)
{
	void	*tmp2;

	free(tmp->next->name);
	free(tmp->next->value);
	tmp2 = tmp->next->next;
	free(tmp->next);
	tmp->next = tmp2;
	main->envp.size--;
}

static void	ms_free_var1(t_main *main)
{
	void		*tmp2;

	free(main->envp.head->name);
	free(main->envp.head->value);
	tmp2 = main->envp.head->next;
	free(main->envp.head);
	main->envp.head = tmp2;
	main->envp.size--;
}

void	ms_unset_name(t_main *main, char *name)
{
	t_nodenv	*tmp;

	if (!main->envp.head)
		return ;
	if (!ft_strncmp(main->envp.head->name, name, ft_strlen(name) + 1))
	{
		ms_free_var1(main);
		return ;
	}
	tmp = main->envp.head;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->next->name, name, ft_strlen(name) + 1))
		{
			ms_free_var2(main, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ms_unset_env_var(t_main *main, t_nodargs *args)
{
	t_nodargs	*tmp;

	tmp = args;
	while (tmp)
	{
		ms_unset_name(main, tmp->var);
		tmp = tmp->next;
	}
}

int	ms_unset(t_main *main, t_nodpars *current)
{
	if (current->flags)
		return (printf("No options allowed for this project.\n"), 1);
	if (current->args)
		ms_unset_env_var(main, current->args);
	return (0);
}
