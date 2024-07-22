/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_trap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:14:37 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:41:44 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	ms_sig_handler_fork(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	if (signal == SIGINT)
		write(1, "\n", 1);
	g_signal = signal;
}

void	ms_sig_handler_hd(int signal)
{
	(void)signal;
	g_signal = SIGINT;
	close(0);
	ft_putchar_fd('\n', 1);
}

void	ms_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal = SIGINT;
	}
}
