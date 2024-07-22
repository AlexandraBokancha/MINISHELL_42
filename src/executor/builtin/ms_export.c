/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:41 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:32:38 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set(char *var, t_main *main)
{
	t_nodenv	*new;
	int			i;

	if (ms_name_format(var))
		return (1);
	new = ms_check_node(main, var);
	if (new)
		main->envp.size++;
	i = 0;
	new->name = ms_envp_name(var, &i);
	if (!new->name)
		ms_exit(main, ms_printerror("Malloc error\n", "", "", 1));
	if (ms_no_equal(var))
		new->exp = 1;
	else
	{
		new->exp = 0;
		new->value = ft_strdup(&var[i]);
		if (!new->value)
			ms_exit(main, ms_printerror("Malloc error\n", "", "", 1));
	}
	return (0);
}

int	ms_env_format(t_main *main, t_nodpars *current)
{
	t_nodargs	*tmp;
	int			err;

	tmp = current->args;
	while (tmp)
	{
		if (ms_fake_flag(tmp->var))
			return (2);
		err = ms_set(tmp->var, main);
		if (err && tmp == current->args)
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			if (!tmp->next)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ms_export_print(t_main *main)
{
	t_nodenv	*tmp;

	tmp = main->envp.head;
	while (tmp)
	{
		if (!tmp->exp)
			printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("export %s\n", tmp->name);
		tmp = tmp->next;
	}
}

int	ms_export(t_main *main, t_nodpars *current)
{
	int	err;

	if (current->flags)
		return (printf("No options allowed for this project.\n"));
	if (current->args)
	{
		err = ms_env_format(main, current);
		if (err)
			return (err);
	}
	else
		ms_export_print(main);
	return (0);
}
