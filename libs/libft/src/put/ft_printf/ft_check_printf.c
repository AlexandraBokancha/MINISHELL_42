/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:54:26 by eschussl          #+#    #+#             */
/*   Updated: 2024/02/07 15:44:45 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_checkflags(const char c, t_printfstruct *structure)
{
	if (c == '0')
		structure->zero = 1;
	if (c == ' ')
		structure->space = 1;
	if (c == '+')
		structure->plus = 1;
	if (c == '-')
		structure->minus = 1;
	if (c == '#')
		structure->hash = 1;
}

static int	ft_bypassnum(const char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		i++;
	return (i);
}

void	ft_check_printf(const char *str, t_printfstruct *structure)
{
	int	i;

	i = 0;
	while (ft_isflag(str[i]) && str[i])
		ft_checkflags(str[i++], structure);
	if (str[i] >= '1' && str[i] <= '9' )
	{
		structure->v_width = ft_atoi(&str[i]);
		i = ft_bypassnum(str, i);
	}
	if (str[i] == '.')
	{
		i++;
		structure->precision = 1;
		structure->v_precision = ft_atoi(&str[i]);
		i = ft_bypassnum(str, i);
	}
	if (ft_isspec(str[i]) && str[i])
	{
		structure->specifier = str[i];
		i++;
	}
	structure->flag_size = i;
}
