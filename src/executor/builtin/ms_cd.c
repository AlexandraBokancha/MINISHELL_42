/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:35 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 19:20:41 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_current_pwd(t_main *main, char *new, char *old)
{
	t_nodenv	*tmp;

	tmp = main->envp.head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "OLDPWD", 7))
		{
			free(tmp->value);
			tmp->value = old;
		}
		else if (!ft_strncmp(tmp->name, "PWD", 4))
		{
			tmp->value = ft_strdup(new);
			if (!tmp->value)
				ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE);
		}
		tmp = tmp->next;
	}
}

void	ms_set_env(t_main *main)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ms_env_elem(main, "PWD");
	if (!old_pwd)
		return ;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	ms_set_current_pwd(main, new_pwd, old_pwd);
	free(new_pwd);
}

int	ms_check_home(t_main *main, t_nodpars *current)
{
	char	*home;

	home = ms_env_elem(main, "HOME");
	if (!home || (home && chdir(home) == -1))
		return (printf("%s: HOME not set\n", current->builtin), MS_ERROR_CODE);
	return (0);
}

static int	ms_check_cddir(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
		return (ms_printerror("getcwd(): ", "", strerror(errno),
				MS_MISSING_DIR));
	free(dir);
	return (0);
}

int	ms_cd(t_main *main, t_nodpars *current)
{
	if (!current->args || (current->args && current->args->var[0] == '~'
			&& !current->args->var[1]))
	{
		if (ms_check_home(main, current))
			return (1);
	}
	else if (current->args && !current->args->next)
	{
		if (ms_check_cddir())
			return (1);
		if (chdir(current->args->var) == -1)
			return (ft_putstr_fd(" No such file or directory\n", 2), 1);
		else if (access(current->args->var, F_OK) == 0
			&& !opendir(current->args->var))
			return (ms_printerror("cd: ", current->args->var,
					": Not a directory", 1));
	}
	else
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	ms_set_env(main);
	return (0);
}
