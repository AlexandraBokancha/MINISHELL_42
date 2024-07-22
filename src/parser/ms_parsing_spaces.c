/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:54:14 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 17:24:56 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static void	ms_add_space(t_main *main, t_nodlex *previous, t_nodlex *actual,
		t_piplex *current)
{
	int	sizefirst;
	int	sizelast;

	if (actual->type != word || !ms_check_space(actual->word))
		return ;
	ms_size_words(actual->word, &sizefirst, &sizelast);
	ms_new_space_nodlex(main, actual, current);
	if (sizelast)
	{
		ms_last_node(main, actual->next, current);
		ms_last_word(main, actual, actual->next->next, sizelast);
	}
	if (sizefirst)
		ms_edit_first_word(main, actual, sizefirst);
	else
		ms_destroy_node(previous, actual, current);
}

static void	ms_join_words(t_main *main, t_nodlex *first, t_piplex *current)
{
	char	*strtmp;
	void	*ptmp;

	strtmp = ft_strjoin(first->word, first->next->word);
	if (!strtmp)
		ms_exit(main, ms_printerror("Malloc error", strerror(errno), "",
				MS_ERROR_CODE));
	free(first->word);
	first->word = strtmp;
	first->type = word;
	ptmp = first->next->next;
	if (first->next->word)
		free(first->next->word);
	free(first->next);
	first->next = ptmp;
	ms_iter_index(first->next, current, -1);
}

void	ms_parsing_spaces(t_main *main, t_piplex *current)
{
	t_nodlex	*tmp;

	ms_add_space(main, NULL, current->head, current);
	tmp = current->head;
	while (tmp->next)
	{
		if (tmp->next->type == word)
			ms_add_space(main, tmp, tmp->next, current);
		tmp = tmp->next;
	}
	tmp = current->head;
	while (tmp->next)
	{
		if ((tmp->type == word || tmp->type == squote || tmp->type == dquote)
			&& (tmp->next->type == word || tmp->next->type == squote
				|| tmp->next->type == dquote))
			ms_join_words(main, tmp, current);
		else
			tmp = tmp->next;
	}
}
