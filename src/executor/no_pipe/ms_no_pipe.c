/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:32 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:04:39 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

int	ms_no_pipe_red(t_nodpars *current, int *red)
{
	int	err;

	err = 0;
	if (!current->input)
		red[0] = STDIN_FILENO;
	else if (current->input)
		err = ms_input(current, red);
	if (err)
		return (err);
	if (!current->output)
		red[1] = STDOUT_FILENO;
	else if (current->output)
		err = ms_output(current, red);
	return (err);
}

void	ms_init_child(t_main *main, int *red)
{
	pid_t	pid;

	signal(SIGQUIT, ms_sig_handler_fork);
	signal(SIGINT, ms_sig_handler_fork);
	pid = fork();
	if (pid == -1)
		ms_exit(main, MS_FORK_ERROR);
	if (pid == 0)
	{
		ms_dup(main, red, red);
		if (execve(main->exec.cmdpath, main->exec.cmdtab, \
			main->exec.envptab) == -1)
			ms_exit(main, ms_printerror("Execve error\n", strerror(errno), "",
					MS_EXECVE_ERROR));
	}
	if (red[0])
		close(red[0]);
	if (red[1] != 1)
		close(red[1]);
}

void	ms_simple_cmd(t_main *main, int *red)
{
	int	status;
	int	sig;

	ms_init_child(main, red);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		if (status == SIGINT || status == SIGKILL)
			return ;
		sig = WTERMSIG(status);
		if (sig == 3)
		{
			main->exitcode = 131;
			return ;
		}
		main->exitcode = 139;
		printf("Child process terminated by signal %d\n", sig);
		return ;
	}
	main->exitcode = WEXITSTATUS(status);
}

void	ms_no_pipe(t_main *main)
{
	int	red[2];
	int	err;

	red[0] = 0;
	red[1] = 1;
	if (main->parser.head->cmd && !main->parser.head->cmd[0])
		return ;
	err = ms_no_pipe_red(main->parser.head, red);
	if (err)
		return (main->exitcode = err, (void)err);
	if (!main->parser.head->cmd && !main->parser.head->builtin)
	{
		ms_check_access(main, red);
		return ;
	}
	if (ft_ispath(main->parser.head->cmd)
		|| ft_ispath(main->parser.head->builtin))
		err = ms_no_pipe_frompath(main, main->parser.head);
	else if (main->parser.head->cmd)
		err = ms_no_pipe_nopath(main, main->parser.head);
	if (err)
		return (main->exitcode = err, (void)err);
	ms_execute_no_pipe(main, red);
}
