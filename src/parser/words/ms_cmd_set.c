/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:10:32 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:02:43 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_builtin(char *word)
{
	if (!ft_strncmp(word, "echo", 5))
		return (1);
	if (!ft_strncmp(word, "cd", 3))
		return (1);
	if (!ft_strncmp(word, "export", 7))
		return (1);
	if (!ft_strncmp(word, "pwd", 4))
		return (1);
	if (!ft_strncmp(word, "env", 4))
		return (1);
	if (!ft_strncmp(word, "unset", 6))
		return (1);
	if (!ft_strncmp(word, "exit", 5))
		return (1);
	return (0);
}

void	ms_binary_cmd(t_main *main, t_nodlex *current, t_nodpars *curpars)
{
	if (ms_is_builtin(current->word))
	{
		curpars->builtin = ft_strdup(current->word);
		if (!curpars->builtin)
			ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE));
	}
	else
	{
		curpars->cmd = ft_strdup(current->word);
		if (!curpars->cmd)
			ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE));
	}
	current->type = other;
	ms_args(main, current->next, curpars);
}

void	ms_cmd_set(t_main *main, t_piplex *curlex, t_nodpars *curpars)
{
	t_nodlex	*tmp;

	tmp = curlex->head;
	while (tmp)
	{
		if ((tmp->type == word || tmp->type == squote || tmp->type == dquote)
			&& tmp->word[0])
			return (ms_binary_cmd(main, tmp, curpars));
		tmp = tmp->next;
	}
}
