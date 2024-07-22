/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:07:18 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 15:52:38 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbvalue(int c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] && (c != ft_ctolower(base[i]) && c != ft_ctoupper(base[i])))
		i++;
	return (i);
}

static int	ft_error_alpha(int c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == ft_ctolower(base[i]) || c == ft_ctoupper(base[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_base(const char *str, const char *base, int *i)
{	
	int	sign;
	int	res;
	int	baselen;

	baselen = (ft_strlen(base));
	sign = 1;
	res = 0;
	while (str[*i] == ' ')
		*i = *i + 1;
	if (str[*i] == '-')
		sign = -sign;
	while (str[*i] && ft_error_alpha(str[*i], base) == 0)
	{
		res = res * baselen + ft_nbvalue(str[*i], base);
		*i = *i + 1;
	}
	return (res);
}
