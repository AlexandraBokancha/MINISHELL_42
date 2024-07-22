/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:48:08 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/07 15:35:31 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_point(size_t nb)
{
	char	*str;
	char	*base;
	int		nb_len;

	nb_len = ft_flen(nb);
	base = "0123456789abcdef";
	str = (char *) ft_calloc(sizeof(char), nb_len + 1);
	if (!str)
		return (NULL);
	str[nb_len] = 0;
	while (nb_len--)
	{
		if (str[nb_len] == '-')
			break ;
		str[nb_len] = base[nb % 16];
		nb = nb / 16;
	}
	return (str);
}

static char	*ft_prefix(t_printfstruct structure)
{
	char	*str;
	int		size;
	int		i;

	size = 2;
	if (structure.plus || structure.space)
		size++;
	str = ft_setalloc(sizeof(char), size + 1, ' ');
	if (!str)
		return (NULL);
	i = size - 1;
	str[i] = 'x';
	str[i - 1] = '0';
	if (structure.plus)
		str[i - 2] = '+';
	else if (structure.space)
		str[i - 2] = ' ';
	return (str);
}

int	ft_p_fd(t_printfstruct structure, size_t nb, int fd)
{
	char	*str;
	int		count;
	char	*str2;
	char	*prefix;

	if (nb == 0)
		return (ft_s_fd(structure, "(nil)", fd));
	prefix = ft_prefix(structure);
	if (!prefix)
		return (0);
	str = ft_itoa_point(nb);
	if (!str)
		return (0);
	str2 = ft_pbis(structure, str, prefix);
	if (!str2)
		return (0);
	count = ft_putlstr_fd(str2, ft_strlen(str2), fd);
	free (str2);
	return (count);
}
