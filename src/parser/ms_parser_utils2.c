/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:21:37 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 17:43:04 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_new_space_nodlex(t_main *main, t_nodlex *previous, t_piplex *current)
{
	t_nodlex	*new;

	new = ft_calloc(1, sizeof(t_nodlex));
	if (!new)
		ms_exit(main, ms_printerror("Malloc error", strerror(errno), "",
				MS_ERROR_CODE));
	new->next = previous->next;
	previous->next = new;
	new->type = space;
	new->index = previous->index + 1;
	ms_iter_index(new->next, current, 1);
}

void	ms_size_words(char *str, int *sfirst, int *slast)
{
	int	ignore;

	ignore = 0;
	*sfirst = 0;
	*slast = 0;
	while (str[*sfirst] && str[*sfirst] != ' ')
		*sfirst = *sfirst + 1;
	while (str[*sfirst + ignore] && str[*sfirst + ignore] == ' ')
		ignore++;
	if (str[*sfirst + ignore])
	{
		while (str[*sfirst + ignore + *slast])
			*slast = *slast + 1;
	}
}

void	ms_destroy_node(t_nodlex *previous, t_nodlex *actual, t_piplex *current)
{
	void	*tmp;

	if (!previous)
		if (actual->word)
			free(actual->word);
	tmp = actual->next;
	free(actual);
	if (previous)
	{
		previous->next = tmp;
		ms_iter_index(previous->next, current, -1);
	}
	else
	{
		current->head = tmp;
		ms_iter_index(current->head, current, -1);
	}
}

void	ms_edit_first_word(t_main *main, t_nodlex *current, int size)
{
	char	*res;
	int		i;

	i = -1;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		ms_exit(main, ms_printerror("Malloc error", strerror(errno), "",
				MS_ERROR_CODE));
	while (++i < size)
		res[i] = current->word[i];
	res[i] = 0;
	free(current->word);
	current->word = res;
}

void	ms_last_word(t_main *main, t_nodlex *ref, t_nodlex *current, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	current->word = ft_calloc(size + 1, sizeof(char));
	if (!current->word)
		ms_exit(main, ms_printerror("Malloc error", strerror(errno), "",
				MS_ERROR_CODE));
	while (ref->word[i] && ref->word[i] != ' ')
		i++;
	while (ref->word[i] && ref->word[i] == ' ')
		i++;
	while (ref->word[i])
		current->word[j++] = ref->word[i++];
}
