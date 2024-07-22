/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:33:50 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 16:24:47 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

void	ms_clean_shell(t_main *main, char *line)
{
	main->ilex = 0;
	free(line);
	ms_free_lexer(main);
	ms_free_exec(main);
	ms_free_parser(main);
	ms_here_doc_del();
	if (g_signal == SIGINT)
	{
		main->exitcode = 130;
		g_signal = 0;
	}
	main->activepipe = 0;
}

void	ms_routine(t_main *main)
{
	char	*line;
	int		err;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ms_sig_handler);
		line = readline("\033[31mMinishell > \e[0m");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			ms_clean_shell(main, line);
			break ;
		}
		if (line && *line)
			add_history(line);
		main->lexer.size = 0;
		ms_lexer(main, line);
		err = ms_parser(main);
		if (err)
			ms_error(main, err);
		else
			ms_executor(main);
		ms_clean_shell(main, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	static t_main	main;

	(void)argv;
	if (argc != 1)
		return (printf("Too many arguments\n"), 1);
	ms_envp(&main, envp);
	ms_routine(&main);
	ms_free_envp(&main);
	if (g_signal)
		main.exitcode = g_signal;
	return (main.exitcode);
}
