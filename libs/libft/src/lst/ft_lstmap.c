/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:40:45 by eschussl          #+#    #+#             */
/*   Updated: 2023/11/17 03:31:38 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lst_change(t_list *lst, void *(*f)(void *))
{
	t_list	*new_list;
	t_list	*current;

	current = lst;
	new_list = NULL;
	while (current)
	{
		ft_lstadd_back(&new_list, ft_lstnew(f(current->content)));
		current = current->next;
	}
	return (new_list);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	new_list = lst_change(lst, f);
	return (new_list);
}
