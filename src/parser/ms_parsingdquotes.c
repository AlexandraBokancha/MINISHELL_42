/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsingdquotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:39:04 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 16:58:40 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_parsingdquotes(t_main *main, t_piplex *current)
{
	t_nodlex	*tmp;
	int			i;

	tmp = current->head;
	while (tmp)
	{
		if (tmp->type == dquote)
		{
			i = 0;
			while (tmp->word[i])
			{
				if (tmp->word[i] == '$')
				{
					ms_build(main, tmp);
					tmp = tmp->next;
					break ;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
