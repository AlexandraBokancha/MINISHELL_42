/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:28:37 by eschussl          #+#    #+#             */
/*   Updated: 2024/01/16 17:04:06 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	count += ft_strread(str, args);
	va_end(args);
	return (count);
}
/* int	main()
{
	char d = 45;

	//char *d = "yoooo";
	printf("| count : %d\n", ft_printf("%+ x", &d)); 
	printf("| count : %d\n", printf("%+ x", &d));
	//printf("%d", printf("yo %0-#+154.4556t\n", d));
	// ft_printf("char c : %-10c", d);
	//s = "yo";
	//printf ("%-ci%-cp%4cs%-11cxssd\n");
	//printf("%d\n", ft_printf(%-ci%-cp%4cs%-11cx", 'a', 'b', 'c', 'd'));
	// ft_printf("|0123|\n");
	// printf("%d\n", printf("|% -.25s|\n", s));
}  */
