/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percentsign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:44:47 by eschussl          #+#    #+#             */
/*   Updated: 2024/01/16 17:07:36 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_percentsign(t_printfstruct structure, va_list args)
{
	int	count;

	count = 0;
	if (structure.specifier == 'c')
		count = ft_c(structure, va_arg(args, int));
	else if (structure.specifier == 's')
		count = ft_s(structure, va_arg(args, char *));
	else if (structure.specifier == 'p')
		count = ft_p(structure, va_arg(args, size_t));
	else if (structure.specifier == 'd' || structure.specifier == 'i')
		count = ft_i(structure, va_arg(args, int));
	else if (structure.specifier == 'u')
		count = ft_u(structure, va_arg(args, unsigned int));
	else if (structure.specifier == 'x' || structure.specifier == 'X')
		count = ft_x(structure, va_arg(args, unsigned int));
	else if (structure.specifier == '%')
		count = ft_putlchar('%');
	return (count);
}
