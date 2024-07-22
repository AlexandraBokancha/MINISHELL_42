/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_output_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:40:35 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 17:53:08 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_build_output_node(t_main *main, t_nodpars *current, char *word,
		bool value)
{
	t_nodred	*tmp;
	t_nodred	*new;

	tmp = NULL;
	new = ft_calloc(sizeof(t_nodred), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	if (!current->output)
		current->output = new;
	else
	{
		tmp = current->output;
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

static int	ms_append(t_main *main, t_nodlex *current, t_nodpars *curpars)
{
	if (current->type == append && current->next && (current->next->type == word
			|| current->next->type == squote || current->next->type == dquote))
	{
		ms_build_output_node(main, curpars, current->next->word, true);
		current->next->type = other;
	}
	else if (current->type == append && current->next
		&& current->next->type == space && current->next->next
		&& (current->next->next->type == word
			|| current->next->next->type == squote
			|| current->next->next->type == dquote))
	{
		ms_build_output_node(main, curpars, current->next->next->word, true);
		current->next->next->type = other;
	}
	else if (current->type == append)
		return (1);
	return (0);
}

static int	ms_redirect_output(t_main *main, t_nodlex *current,
		t_nodpars *curpars)
{
	if (current->type == output && current->next && current->next->type == space
		&& current->next->next && (current->next->next->type == word
			|| current->next->next->type == squote
			|| current->next->next->type == dquote))
	{
		ms_build_output_node(main, curpars, current->next->next->word, false);
		current->next->next->type = other;
	}
	else if (current->type == output && current->next
		&& (current->next->type == word || current->next->type == squote
			|| current->next->type == dquote))
	{
		ms_build_output_node(main, curpars, current->next->word, false);
		current->next->type = other;
	}
	else if (current->type == output)
		return (1);
	return (0);
}

int	ms_output_set(t_main *main, t_piplex *curlex, t_nodpars *curpars)
{
	t_nodlex	*tmp;

	tmp = curlex->head;
	while (tmp)
	{
		if (ms_redirect_output(main, tmp, curpars) || ms_append(main, tmp,
				curpars))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
