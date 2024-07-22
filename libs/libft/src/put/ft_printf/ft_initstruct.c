/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:26 by eschussl          #+#    #+#             */
/*   Updated: 2024/01/16 17:06:58 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_initstruct(t_printfstruct *new_struct)
{
	new_struct->hash = 0;
	new_struct->plus = 0;
	new_struct->space = 0;
	new_struct->minus = 0;
	new_struct->zero = 0;
	new_struct->v_width = 0;
	new_struct->precision = 0;
	new_struct->v_precision = 0;
	new_struct->specifier = 0;
	new_struct->flag_size = 0;
}
