/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_nodefill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:28:21 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 16:43:02 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodlex	*ms_twochar(t_main *main, char *str, t_nodlex *prev,
t_piplex *current)
{
	t_nodlex	*new;

	if ((str[main->ilex] == '<' && str[main->ilex + 1] && str[main->ilex
				+ 1] == '<') || (str[main->ilex] == '>' && str[main->ilex + 1]
			&& str[main->ilex + 1] == '>'))
		new = ms_new_nodlex(main, prev, current);
	if (str[main->ilex] == '<' && str[main->ilex + 1] && str[main->ilex
			+ 1] == '<')
	{
		main->ilex += 2;
		new->type = here_doc;
		return (new);
	}
	if (str[main->ilex] == '>' && str[main->ilex + 1] && str[main->ilex
			+ 1] == '>')
	{
		main->ilex += 2;
		new->type = append;
		return (new);
	}
	return (NULL);
}

t_nodlex	*ms_onechar(t_main *main, char *str, t_nodlex *prev,
		t_piplex *current)
{
	t_nodlex	*new;

	if (str[main->ilex] == '<' || str[main->ilex] == '>')
		new = ms_new_nodlex(main, prev, current);
	if (str[main->ilex] == '<')
	{
		main->ilex++;
		new->type = input;
		return (new);
	}
	if (str[main->ilex] == '>')
	{
		main->ilex++;
		new->type = output;
		return (new);
	}
	return (NULL);
}

t_nodlex	*ms_string(t_main *main, char *str, t_nodlex *prev,
		t_piplex *current)
{
	t_nodlex	*new;
	int			size;
	int			i;

	size = ms_str_size(&str[main->ilex]);
	if (!str[main->ilex + size - 1])
	{
		while (str[main->ilex])
			main->ilex++;
		return (NULL);
	}
	if (!size)
		return (NULL);
	new = ms_new_nodlex(main, prev, current);
	new->type = word;
	new->word = ft_calloc(sizeof(char), size + 1);
	if (!new->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	i = 0;
	while (i < size)
		new->word[i++] = str[main->ilex++];
	new->word[i] = 0;
	return (new);
}

t_nodlex	*ms_space(t_main *main, char *str, t_nodlex *prev,
		t_piplex *current)
{
	t_nodlex	*new;

	new = NULL;
	if (str[main->ilex] == ' ' || str[main->ilex] == '\n'
		|| str[main->ilex] == '\t')
	{
		new = ft_calloc(sizeof(t_nodlex), 1);
		if (!new)
			ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
					MS_ERROR_CODE));
		new->type = space;
		if (current->size == 0)
			new->index = 0;
		else
			new->index = prev->index + 1;
		current->size += 1;
		while (str[main->ilex] && (str[main->ilex] == ' '
				|| str[main->ilex] == '\t' || str[main->ilex] == '\n'))
			main->ilex += 1;
	}
	return (new);
}

void	ms_nodefill(t_main *main, t_piplex *node, char *str)
{
	t_nodlex	*new;
	t_nodlex	*tmp;

	tmp = NULL;
	while (str[main->ilex] && str[main->ilex] != '|')
	{
		new = ms_twochar(main, str, tmp, node);
		if (!new)
			new = ms_onechar(main, str, tmp, node);
		if (!new)
			new = ms_string(main, str, tmp, node);
		if (!new)
			new = ms_space(main, str, tmp, node);
		if (!node->head)
			node->head = new;
		else
			tmp->next = new;
		tmp = new;
	}
}
