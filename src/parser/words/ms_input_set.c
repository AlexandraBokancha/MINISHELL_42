/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:39:37 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 17:50:56 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_build_input_node(t_main *main, t_nodpars *current, char *word,
		bool value)
{
	t_nodred	*tmp;
	t_nodred	*new;

	tmp = NULL;
	new = ft_calloc(sizeof(t_nodred), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	if (!current->input)
		current->input = new;
	else
	{
		tmp = current->input;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->word = ft_strdup(word);
	if (!new->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	new->mod = value;
}

static int	ms_redirect_input(t_main *main, t_nodlex *tmp, t_nodpars *curpars)
{
	if (tmp->type == input && tmp->next && tmp->next->type == space
		&& tmp->next->next && (tmp->next->next->type == word
			|| tmp->next->next->type == dquote
			|| tmp->next->next->type == squote))
	{
		ms_build_input_node(main, curpars, tmp->next->next->word, false);
		tmp->next->next->type = other;
	}
	else if (tmp->type == input && tmp->next && (tmp->next->type == word
			|| tmp->next->type == dquote || tmp->next->type == squote))
	{
		ms_build_input_node(main, curpars, tmp->next->word, false);
		tmp->next->type = other;
	}
	else if (tmp->type == input)
		return (1);
	return (0);
}

int	ms_input_set(t_main *main, t_piplex *curlex, t_nodpars *curpars)
{
	t_nodlex	*tmp;

	tmp = curlex->head;
	while (tmp)
	{
		if (ms_redirect_input(main, tmp, curpars) || ms_here_doc(main, tmp,
				curpars))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
