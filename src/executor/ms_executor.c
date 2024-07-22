/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:31:01 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 18:11:51 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_exit_cmd(t_main *main)
{
	t_nodpars	*tmp;

	tmp = main->parser.head;
	while (tmp)
	{
		if (tmp->builtin && !ft_strncmp(tmp->builtin, "exit", 4))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ms_executor(t_main *main)
{
	if (!ms_check_exit_cmd(main))
		main->exitcode = 0;
	ms_envp_tab(main);
	ms_path_init(main);
	if (main->parser.size > 1)
		ms_fork(main);
	else if (main->parser.size == 1)
		ms_no_pipe(main);
}
