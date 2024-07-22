/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:04:53 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 17:43:23 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_parsing_exitcode_env(t_nodlex *tmp, t_main *main)
{
	free(tmp->word);
	tmp->word = ft_itoa(main->exitcode);
	if (!tmp->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
}

void	ms_parsing_word_env(t_nodlex *tmp, t_main *main)
{
	free(tmp->word);
	tmp->word = ft_strdup("$");
	if (!tmp->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
}

void	ms_parsing_var_env(t_nodlex *tmp, t_nodlex *tmp2, t_piplex *current)
{
	void	*void_tmp;

	free(tmp->word);
	tmp->word = tmp->next->word;
	tmp->type = word;
	void_tmp = tmp->next->next;
	free(tmp->next);
	tmp->next = void_tmp;
	tmp2 = tmp;
	while (tmp2)
	{
		tmp2->index--;
		tmp2 = tmp2->next;
	}
	current->size--;
}

void	ms_last_node(t_main *main, t_nodlex *previous, t_piplex *current)
{
	t_nodlex	*new;

	new = ft_calloc(1, sizeof(t_nodlex));
	if (!new)
		ms_exit(main, ms_printerror("Malloc error", "", "", MS_ERROR_CODE));
	new->next = previous->next;
	previous->next = new;
	new->type = word;
	new->index = previous->index + 1;
	ms_iter_index(new->next, current, 1);
}

void	ms_iter_index(t_nodlex *first, t_piplex *current, int value)
{
	t_nodlex	*tmp;

	current->size += value;
	tmp = first;
	while (tmp)
	{
		tmp->index += value;
		tmp = tmp->next;
	}
}
