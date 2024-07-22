/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:30:53 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:39:39 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_dup(t_main *main, int *input, int *output)
{
	if (input[0])
	{
		if (dup2(input[0], STDIN_FILENO) == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
		close(input[0]);
	}
	if (output[1] != 1)
	{
		if (dup2(output[1], STDOUT_FILENO) == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
		close(output[1]);
	}
	if (input != output)
		ms_pip_close(main);
}
