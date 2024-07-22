/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:25:14 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/21 15:15:26 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_hex(unsigned int nb)
{
	char	*base;
	int		nb_len;
	char	*str;

	base = "0123456789abcdef";
	nb_len = ft_flen(nb);
	str = ft_calloc(sizeof(char), nb_len + 1);
	if (!str)
		return (NULL);
	str[nb_len] = '\0';
	while (nb_len--)
	{
		if (str[nb_len] == '-')
			break ;
		str[nb_len] = base[nb % 16];
		nb = nb / 16;
	}
	return (str);
}

static int	ft_zer_fd(t_printfstruct structure, int fd)
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

int	ft_x_fd(t_printfstruct structure, unsigned int nb, int fd)
{
	int		count;
	char	*str;
	char	*str2;

	if (!nb && structure.precision && !structure.v_precision)
		return (ft_zer_fd(structure, fd));
	if (!nb)
		structure.hash = 0;
	str = ft_itoa_hex(nb);
	if (!str)
		return (0);
	str2 = ft_xbis(structure, str);
	if (!str2)
		return (0);
	count = ft_putlstr_fd(str2, ft_strlen(str2), fd);
	free (str2);
	return (count);
}
