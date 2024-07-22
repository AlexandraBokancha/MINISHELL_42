/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:51:26 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:26:09 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exit_args(t_main *main, t_nodpars *current)
{
	unsigned char	status;
	int				i;

	i = 0;
	status = 0;
	if (!current->args)
		return (0);
	if (current->args->var[i] == '+')
		i++;
	while (current->args->var[i] && (ft_isdigit(current->args->var[i])))
		i++;
	if (current->args->var[i] && main->parser.size == 1)
		return (ft_putstr_fd(" numeric argument required\n", 2), 2);
	if (current->args->next && main->parser.size == 1)
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	status = ft_atoi(current->args->var);
	if (main->parser.size == 1)
		printf("exit\n");
	ms_exit(main, status);
	return (0);
}

int	ms_exit_flags(t_main *main, t_nodpars *current)
{
	unsigned char	status;
	int				i;

	i = 1;
	status = 0;
	if (!current->flags)
		return (0);
	while (current->flags->var[i] && ft_isdigit(current->flags->var[i]))
		i++;
	if (current->flags->var[i] && main->parser.size == 1)
		return (ft_putstr_fd(" numeric argument required\n", 2), 2);
	if (current->flags->next && main->parser.size == 1)
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	status = ft_atoi(current->flags->var);
	printf("exit\n");
	ms_exit(main, status);
	return (0);
}

int	ms_exit_b(t_main *main, t_nodpars *current)
{
	int	err;

	if (current->args || current->flags)
	{
		if (current->args && current->flags)
			return (ft_putstr_fd(" too many arguments\n", 2), 1);
		err = ms_exit_args(main, current);
		if (err)
			return (err);
		err = ms_exit_flags(main, current);
		if (err)
			return (err);
	}
	else if (!current->flags && !current->args)
	{
		if (main->parser.size == 1)
			printf("exit\n");
		ms_exit(main, 0);
	}
	return (0);
}
