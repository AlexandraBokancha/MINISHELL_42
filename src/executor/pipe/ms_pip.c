/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:01 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:46:50 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pip_init(t_main *main)
{
	int	i;

	main->exec.pid = ft_calloc(main->parser.size, sizeof(int));
	if (!main->exec.pid)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	main->exec.pipefd = ft_calloc(main->parser.size, sizeof(int *));
	if (!main->exec.pipefd)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	i = 0;
	while (i < main->parser.size)
	{
		main->exec.pipefd[i] = ft_calloc(2, sizeof(int));
		if (!main->exec.pipefd[i])
			ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE));
		if (pipe(main->exec.pipefd[i++]) == -1)
			ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE));
	}
	main->activepipe = 1;
}

void	ms_pip_close(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->parser.size)
	{
		close(main->exec.pipefd[i][0]);
		close(main->exec.pipefd[i][1]);
		i++;
	}
}
