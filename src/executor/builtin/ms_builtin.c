/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:07:05 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:09:30 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_fd_cpy(t_main *main, int *fdtmp, int *input, int *output)
{
	if (input[0])
	{
		fdtmp[0] = dup(STDIN_FILENO);
		if (fdtmp[0] == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
	}
	if (output[1] != 1)
	{
		fdtmp[1] = dup(STDOUT_FILENO);
		if (fdtmp[1] == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
	}
	ms_dup(main, input, output);
}

void	ms_builtin_exec(t_main *main, t_nodpars *current)
{
	if (!ft_strncmp(current->builtin, "pwd", 3))
		main->exitcode = ms_pwd(current);
	else if (!ft_strncmp(current->builtin, "env", 3))
		main->exitcode = ms_env(main, current);
	else if (!ft_strncmp(current->builtin, "echo", 4))
		main->exitcode = ms_echo(current);
	else if (!ft_strncmp(current->builtin, "cd", 2))
		main->exitcode = ms_cd(main, current);
	else if (!ft_strncmp(current->builtin, "export", 6))
		main->exitcode = ms_export(main, current);
	else if (!ft_strncmp(current->builtin, "unset", 5))
		main->exitcode = ms_unset(main, current);
	else if (!ft_strncmp(current->builtin, "exit", 4))
		main->exitcode = ms_exit_b(main, current);
}

void	ms_builtin(t_main *main, t_nodpars *current, int *input, int *output)
{
	int	fdtmp[2];

	ms_fd_cpy(main, fdtmp, input, output);
	ms_builtin_exec(main, current);
	if (input[0])
	{
		if (dup2(fdtmp[0], STDIN_FILENO) == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
		close(fdtmp[0]);
	}
	if (output[1] != 1)
	{
		if (dup2(fdtmp[1], STDOUT_FILENO) == -1)
			ms_exit(main, ms_printerror("Dup error\n", strerror(errno), "",
					MS_DUP_ERROR));
		close(fdtmp[1]);
	}
}
