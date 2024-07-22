/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:56 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:03:28 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_flags_set(t_main *main, t_nodlex *current, t_nodpars *curpars,
		int index)
{
	t_nodargs	*new;
	t_nodargs	*tmp;

	new = ft_calloc(sizeof(t_nodargs), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	if (!curpars->flags)
		curpars->flags = new;
	else
	{
		tmp = curpars->flags;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->index = index;
	new->var = ft_strdup(current->word);
	if (!new->var)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
}

void	ms_args_set(t_main *main, t_nodlex *current, t_nodpars *curpars,
		int index)
{
	t_nodargs	*new;
	t_nodargs	*tmp;

	new = ft_calloc(sizeof(t_nodargs), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	if (!curpars->args)
		curpars->args = new;
	else
	{
		tmp = curpars->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->index = index;
	new->var = ft_strdup(current->word);
	if (!new->var)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
}

int	ms_is_flag(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

void	ms_args(t_main *main, t_nodlex *current, t_nodpars *curpars)
{
	t_nodlex	*tmp;
	int			index;

	index = 0;
	tmp = current;
	while (tmp)
	{
		if (tmp->type == word || tmp->type == squote || tmp->type == dquote)
		{
			if (tmp->word[0] == '-' && ms_is_flag(tmp->word + 1)
				&& ((curpars->builtin && !curpars->args)
					|| !(curpars->builtin)))
				ms_flags_set(main, tmp, curpars, index);
			else
				ms_args_set(main, tmp, curpars, index);
			index++;
			curpars->size++;
		}
		tmp = tmp->next;
	}
}
