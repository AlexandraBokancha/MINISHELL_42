/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:27:55 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:33:21 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodenv	*ms_check_node(t_main *main, char *var)
{
	t_nodenv	*tmp;
	t_nodenv	*new;

	tmp = main->envp.head;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->name, ft_strlen(tmp->name)))
		{
			free(tmp->name);
			free(tmp->value);
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = main->envp.head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = ft_calloc(sizeof(t_nodenv), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", "", "", 1));
	if (main->envp.size > 0)
		tmp->next = new;
	else
		main->envp.head = new;
	return (new);
}

int	ms_special_c(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

int	ms_name_format(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '=' || ms_special_c(str[0]) != 1)
		return (1);
	while (str[i] && str[i] != '=' && str[i] != ' ')
	{
		if (!ms_special_c(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ms_no_equal(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			return (0);
	}
	return (1);
}

int	ms_fake_flag(char *var)
{
	if (var[0] == '-' && var[1] == '-')
		return (printf("export: --: invalid option\n"));
	return (0);
}
