/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_ter_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:22:13 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/20 14:28:14 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_zeri_fd(t_printfstruct structure, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < structure.v_width)
	{
		count += ft_putlchar_fd(' ', fd);
		i++;
	}
	return (count);
}
