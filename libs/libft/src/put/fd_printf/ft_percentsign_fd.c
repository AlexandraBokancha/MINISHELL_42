/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percentsign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:44:47 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/07 15:34:22 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_percentsign_fd(t_printfstruct structure, va_list args, int fd)
{
	int	count;

	count = 0;
	if (structure.specifier == 'c')
		count = ft_c_fd(structure, va_arg(args, int), fd);
	else if (structure.specifier == 's')
		count = ft_s_fd(structure, va_arg(args, char *), fd);
	else if (structure.specifier == 'p')
		count = ft_p_fd(structure, va_arg(args, size_t), fd);
	else if (structure.specifier == 'd' || structure.specifier == 'i')
		count = ft_i_fd(structure, va_arg(args, int), fd);
	else if (structure.specifier == 'u')
		count = ft_u_fd(structure, va_arg(args, unsigned int), fd);
	else if (structure.specifier == 'x' || structure.specifier == 'X')
		count = ft_x_fd(structure, va_arg(args, unsigned int), fd);
	else if (structure.specifier == '%')
		count = ft_putlchar_fd('%', fd);
	return (count);
}
