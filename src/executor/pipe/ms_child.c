/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:26 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:50:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_cmdcheck(t_main *main, char *cmd)
{
	char	*cmdpath;
	int		i;

	i = -1;
	while (main->exec.path && main->exec.path[++i])
	{
		cmdpath = ms_cmdpath(main->exec.path[i], cmd);
		if (!cmdpath)
			ms_exit(main, ms_printerror("Malloc error\n", "", "",
					MS_ERROR_CODE));
		if (access(cmdpath, F_OK) == 0)
		{
			if (access(cmdpath, X_OK) == 0)
				return (cmdpath);
			free(cmdpath);
			ms_exit(main, ms_printerror("Command not found\n", "", "",
					MS_CMD_NOT_FOUND));
		}
		free(cmdpath);
	}
	return (ms_cmd_on(main, cmd));
}

int	ms_pipe_red(int *input, t_nodpars *current, int *output)
{
	int	err;

	err = ms_check_input(current, input);
	if (err)
		return (err);
	err = ms_check_output(current, output);
	if (err)
		return (err);
	return (err);
}

void	ms_no_path(t_main *main, t_nodpars *current)
{
	main->exec.cmdtab = ms_cmdtab(current->cmd, current, main);
	if (!main->exec.cmdtab)
		ms_exit(main, ms_printerror("Malloc error\n", "", "", MS_ERROR_CODE));
	main->exec.cmdpath = ms_cmdcheck(main, current->cmd);
}

void	ms_frompath(t_main *main, t_nodpars *current)
{
	char	*cmd;

	if (current->cmd)
		cmd = current->cmd;
	else
		cmd = current->builtin;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			main->exec.cmdtab = ms_cmdtab(cmd, current, main);
			if (!main->exec.cmdtab)
				ms_exit(main, ms_printerror("Malloc error\n", "", "", 1));
			main->exec.cmdpath = ft_strdup(cmd);
			if (!main->exec.cmdpath)
				ms_exit(main, ms_printerror("Malloc error\n", "", "",
						MS_ERROR_CODE));
			return ;
		}
		else
			ms_exit(main, ms_printerror("Permission denied\n", "", "", \
				MS_PERMISSION));
	}
	else
		ms_check_dir(main, cmd);
}

void	ms_child(t_main *main, int *input, t_nodpars *current, int *output)
{
	int	res;

	if (current->cmd && !current->cmd[0])
		ms_exit(main, 0);
	signal(SIGQUIT, ms_sig_handler_fork);
	signal(SIGINT, ms_sig_handler_fork);
	res = ms_pipe_red(input, current, output);
	if (res)
		ms_exit(main, res);
	if (!current->cmd && !current->builtin)
		ms_exit(main, 0);
	if (ft_ispath(current->cmd) || ft_ispath(current->builtin))
		ms_frompath(main, current);
	else if (current->cmd)
		ms_no_path(main, current);
	if (current->builtin)
	{
		ms_builtin(main, current, input, output);
		ms_exit(main, 0);
	}
	ms_dup(main, input, output);
	if (execve(main->exec.cmdpath, main->exec.cmdtab, main->exec.envptab) == -1)
		ms_exit(main, ms_printerror("Execve error\n", "", "", MS_EXECVE_ERROR));
}
