/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_no_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:00:36 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:07:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execute_no_pipe(t_main *main, int *red)
{
	if (main->parser.head->builtin)
		ms_builtin(main, main->parser.head, red, red);
	else
		ms_simple_cmd(main, red);
}

void	ms_check_access(t_main *main, int *red)
{
	if (!access(MS_HERE_DOC_FILE, F_OK))
	{
		close(red[0]);
		return ;
	}
	main->exitcode = 0;
}
