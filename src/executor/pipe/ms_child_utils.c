/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:55 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 18:53:31 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_cmd_on(t_main *main, char *cmd)
{
	char	*test1;

	if (access(cmd, F_OK) != 0)
		ms_exit(main, ms_printerror(cmd, ": command not found", "",
				MS_CMD_NOT_FOUND));
	if (access(cmd, X_OK) != 0)
		ms_exit(main, ms_printerror(cmd, ": Permission denied", "",
				MS_PERMISSION));
	test1 = ft_strdup(cmd);
	if (!test1)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (test1);
}

void	ms_check_dir(t_main *main, char *cmd)
{
	if (opendir(cmd))
		ms_exit(main, ms_printerror(cmd, ": Is a directory", "",
				MS_DIRECTORY_ERROR));
	ms_exit(main, ms_printerror("No such file or directory\n", strerror(errno),
			"", MS_MISSING_DIR));
}

int	ms_check_input(t_nodpars *current, int *input)
{
	int	err;

	err = 0;
	if (current->input)
	{
		if (input[0] != -1)
		{
			close(input[0]);
			close(input[1]);
		}
		err = ms_input(current, input);
	}
	else if (input[0] == -1)
		input[0] = STDIN_FILENO;
	if (err)
		return (err);
	return (0);
}

int	ms_check_output(t_nodpars *current, int *output)
{
	int	err;

	err = 0;
	if (current->output)
	{
		if (output[1] != -1)
		{
			close(output[0]);
			close(output[1]);
		}
		err = ms_output(current, output);
	}
	else if (output[1] == -1)
		output[1] = STDOUT_FILENO;
	if (err)
		return (err);
	return (0);
}

void	ms_fork_ending(t_main *main)
{
	pid_t	pid;

	ms_pip_close(main);
	pid = waitpid(-1, &main->status, 0);
	ms_waiting(main, pid);
}
