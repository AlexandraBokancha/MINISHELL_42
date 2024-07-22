/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:18:51 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:06:24 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_here_doc_del(void)
{
	if (!access(MS_HERE_DOC_FILE, F_OK))
		unlink(MS_HERE_DOC_FILE);
}

void	ms_exit_child(t_main *main, int exit_code)
{
	ms_free_lexer(main);
	ms_free_exec(main);
	ms_free_parser(main);
	ms_free_envp(main);
	exit(exit_code);
}

void	ms_exit(t_main *main, int exit_code)
{
	ms_free_lexer(main);
	if (main->activepipe == true)
		ms_pip_close(main);
	ms_free_exec(main);
	ms_free_parser(main);
	ms_free_envp(main);
	ms_here_doc_del();
	exit(exit_code);
}

int	ms_printerror(char *str, char *str1, char *str2, int exit_code)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putchar_fd('\n', 2);
	return (exit_code);
}

void	ms_error(t_main *main, int errorcode)
{
	main->exitcode = errorcode;
	ms_free_lexer(main);
	if (main->activepipe == true)
		ms_pip_close(main);
	ms_free_exec(main);
	ms_free_parser(main);
}
