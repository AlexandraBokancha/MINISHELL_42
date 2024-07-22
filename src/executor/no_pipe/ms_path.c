/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:19:53 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:06:29 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_no_pipe_frompath(t_main *main, t_nodpars *current)
{
	char	*cmd;

	if (current->cmd)
		cmd = current->cmd;
	else
		cmd = current->builtin;
	if (opendir(cmd))
		return (ms_printerror(cmd, ": is a directory", "", MS_DIRECTORY_ON));
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			main->exec.cmdtab = ms_cmdtab(cmd, current, main);
			if (!main->exec.cmdtab)
				return (ms_printerror("Malloc error\n", "", "", MS_ERROR_CODE));
			main->exec.cmdpath = ft_strdup(cmd);
			if (!main->exec.cmdpath)
				return (ms_printerror("Malloc error\n", "", "", MS_ERROR_CODE));
		}
		else
			return (ms_printerror(cmd, ": permission denied", "", 126));
	}
	else
		return (ms_printerror(cmd, ": no such file or directory", "", 127));
	return (0);
}

static int	ms_cmd_check(t_main *main, char *cmd)
{
	if (opendir(cmd))
		return (ms_printerror(cmd, ": command not found", "",
				MS_CMD_NOT_FOUND));
	if (access(cmd, F_OK) != 0)
		return (ms_printerror(cmd, ": command not found", "",
				MS_CMD_NOT_FOUND));
	if (access(cmd, X_OK) != 0)
		return (ms_printerror(cmd, ": command not found", "",
				MS_CMD_NOT_FOUND));
	main->exec.cmdpath = ft_strdup(cmd);
	if (!main->exec.cmdpath)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (0);
}

static int	ms_cmdcheck(t_main *main, char *cmd)
{
	int	i;

	i = -1;
	while (main->exec.path && main->exec.path[++i])
	{
		main->exec.cmdpath = ms_cmdpath(main->exec.path[i], cmd);
		if (!main->exec.cmdpath)
			ms_exit(main, ms_printerror("Malloc error\n", "", "",
					MS_ERROR_CODE));
		if (access(main->exec.cmdpath, F_OK) == 0)
		{
			if (access(main->exec.cmdpath, X_OK) == 0)
				return (0);
			return (ms_printerror(main->exec.cmdpath, ": command not found", "",
					126));
		}
		free(main->exec.cmdpath);
		main->exec.cmdpath = NULL;
	}
	return (ms_cmd_check(main, cmd));
}

int	ms_no_pipe_nopath(t_main *main, t_nodpars *current)
{
	if (!current->cmd[0])
		return (ms_printerror(current->cmd, ": command not found", "",
				MS_CMD_NOT_FOUND));
	main->exec.cmdtab = ms_cmdtab(current->cmd, current, main);
	if (!main->exec.cmdtab)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (ms_cmdcheck(main, current->cmd));
}
