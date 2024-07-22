/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strread_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:30:46 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/20 14:28:05 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strread_fd(const char *str, va_list args, int fd)
{
	int				count;
	int				i;
	t_printfstruct	new_struct;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_initstruct(&new_struct);
			ft_check_printf(&str[i + 1], &new_struct);
			count += ft_percentsign_fd(new_struct, args, fd);
			i += new_struct.flag_size;
		}
		else
			count += ft_putlchar_fd((const char) str[i], fd);
		i++;
	}
	return (count);
}
