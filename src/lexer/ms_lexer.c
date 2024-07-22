/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:23:54 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_ilex(t_main *main, char *str)
{
	while (str[main->ilex] && str[main->ilex] == ' ')
		main->ilex++;
}

void	ms_lexer(t_main *main, char *str)
{
	t_piplex	*new;

	main->lexer.head = ms_new_piplex(main, 0);
	new = main->lexer.head;
	ms_ilex(main, str);
	while (str[main->ilex])
	{
		if (str[main->ilex] == '|')
		{
			if (new == main->lexer.head)
			{
				main->lexer.head->next = ms_new_piplex(main,
						main->lexer.head->index + 1);
				new = main->lexer.head->next;
			}
			else
			{
				new->next = ms_new_piplex(main, new->index + 1);
				new = new->next;
			}
			main->ilex++;
		}
		if (str[main->ilex])
			ms_nodefill(main, new, str);
	}
}
