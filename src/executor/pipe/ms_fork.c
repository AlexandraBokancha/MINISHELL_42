/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noda <noda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:05:58 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 20:32:11 by noda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_fork_middle(t_main *main, t_nodpars *tmp, int *i)
{
	while (tmp->next)
	{
		main->exec.pid[*i] = fork();
		if (main->exec.pid[*i] == -1)
			ms_exit(main, ms_printerror("Fork error\n", "", "", MS_FORK_ERROR));
		if (main->exec.pid[*i] == 0)
			ms_child(main, main->exec.pipefd[*i - 1], tmp,
				main->exec.pipefd[*i]);
		*i += 1;
		tmp = tmp->next;
	}
}

static void	ms_check_sig2(t_main *main, int *i)
{
	if (*i == main->parser.size - 1 && main->status)
	{
		if (WIFSIGNALED(main->status))
		{
			if (main->status != SIGINT && main->status != SIGKILL)
			{
				if (main->sig == 3)
					main->exitcode = 131;
				else
					main->exitcode = 139;
			}
		}
		else
			main->exitcode = WEXITSTATUS(main->status);
	}
}

static void	ms_check_sig1(t_main *main, pid_t pid)
{
	if (WIFSIGNALED(main->status))
	{
		main->sig = WTERMSIG(main->status);
		if (main->sig == 11)
			printf("Child process %d terminated by signal %d\n", pid,
				main->sig);
	}
}

void	ms_waiting(t_main *main, pid_t pid)
{
	int	j;
	int	i;

	j = 0;
	while (pid != -1 && j < main->parser.size)
	{
		main->sig = 0;
		ms_check_sig1(main, pid);
		i = 0;
		while (i < main->parser.size)
		{
			if (main->exec.pid[i] == pid)
			{
				if (i == main->parser.size - 1 && main->status)
					ms_check_sig2(main, &i);
				else if (i == main->parser.size)
					main->exitcode = 0;
				j++;
				break ;
			}
			i++;
		}
		main->status = 0;
		pid = waitpid(-1, &main->status, 0);
	}
}

void	ms_fork(t_main *main)
{
	int			i;
	int			fake[2];
	t_nodpars	*tmp;

	i = 1;
	fake[0] = -1;
	fake[1] = -1;
	ms_pip_init(main);
	signal(SIGQUIT, ms_sig_handler_fork);
	signal(SIGINT, ms_sig_handler_fork);
	main->exec.pid[0] = fork();
	if (main->exec.pid[0] == -1)
		ms_exit(main, ms_printerror("Fork error\n", "", "", MS_FORK_ERROR));
	if (main->exec.pid[0] == 0)
		ms_child(main, fake, main->parser.head, main->exec.pipefd[0]);
	ms_fork_middle(main, main->parser.head->next, &i);
	main->exec.pid[i] = fork();
	if (main->exec.pid[i] == -1)
		ms_exit(main, ms_printerror("Fork error\n", "", "", MS_FORK_ERROR));
	tmp = main->parser.head;
	while (tmp->next)
		tmp = tmp->next;
	if (main->exec.pid[i] == 0)
		ms_child(main, main->exec.pipefd[i - 1], tmp, fake);
	ms_fork_ending(main);
}
