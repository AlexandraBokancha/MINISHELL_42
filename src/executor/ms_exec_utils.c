/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:36 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:40:40 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_mod(t_nodred *first)
{
	t_nodred	*tmp;

	tmp = first;
	while (tmp)
	{
		if (tmp->mod == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**ms_cmdtab_init(t_main *main, t_nodpars *current, char *cmd)
{
	char	**cmdtab;

	cmdtab = ft_calloc(current->size + 2, sizeof(char *));
	if (!cmdtab)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	cmdtab[0] = ft_strdup(cmd);
	if (!cmdtab[0])
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (cmdtab);
}

t_nodargs	*ms_args_search(t_nodpars *current, int index)
{
	t_nodargs	*tmp;

	tmp = current->flags;
	while (tmp)
	{
		if (tmp->index == index)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = current->args;
		while (tmp)
		{
			if (tmp->index == index)
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

char	**ms_cmdtab(char *cmd, t_nodpars *current, t_main *main)
{
	t_nodargs	*tmp;
	char		**cmdtab;
	int			i;
	int			index;

	cmdtab = ms_cmdtab_init(main, current, cmd);
	i = 1;
	index = 0;
	while (index < current->size)
	{
		tmp = ms_args_search(current, index);
		if (!tmp)
			return (cmdtab);
		cmdtab[i] = ft_strdup(tmp->var);
		i++;
		index++;
	}
	return (cmdtab);
}

char	*ms_cmdpath(char *path, char *cmd)
{
	char	*res;
	int		i;
	int		j;

	res = ft_calloc(ft_strlen(path) + ft_strlen(cmd) + 2, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (path[++i])
		res[i] = path[i];
	res[i++] = '/';
	j = -1;
	while (cmd[++j])
		res[i + j] = cmd[j];
	res[i + j] = 0;
	return (res);
}
