/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:39 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:22:14 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_n_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[i] && flag[i] != ' ')
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ms_fake_echo_flag(t_nodpars *current)
{
	t_nodargs	*tmp;
	int			res;
	int			res2;

	res2 = 0;
	tmp = current->flags;
	while (tmp)
	{
		res = ms_is_n_flag(tmp->var);
		if (res2 == 0 && res == 1)
			res2 = 1;
		if (!res)
		{
			printf("%s", tmp->var);
			if (current->args || tmp->next)
				printf(" ");
		}
		tmp = tmp->next;
	}
	return (res2);
}

int	ms_echo(t_nodpars *current)
{
	t_nodargs	*tmp;
	int			flag;

	flag = 0;
	if (current->flags)
		flag = ms_fake_echo_flag(current);
	tmp = current->args;
	while (tmp)
	{
		printf("%s", tmp->var);
		if (tmp->var[0] && tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	if (!flag)
		printf("\n");
	return (0);
}
