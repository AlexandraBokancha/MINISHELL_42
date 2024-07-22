/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:50:27 by eschussl          #+#    #+#             */
/*   Updated: 2024/04/10 18:12:22 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

long	ft_atolle(char *nptr, int *i)
{
	int	sign;
	int	res;
	int	saved;

	sign = 1;
	res = 0;
	if (!nptr)
		return (0);
	while (nptr[*i] && (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13)))
		*i += 1;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			sign = -sign;
		*i += 1;
	}
	saved = *i;
	while (nptr[*i] && nptr[*i] != ' ')
	{
		res = res * 10 + (nptr[*i] - '0');
		*i += 1;
	}
	if (*i == saved)
		*i = -1;
	return (res * sign);
}

/*Fonction atolle renvoie un long passe en argument un pointeur 
*i renvoyant l'index du caractere suivant le nombre lu.
Si aucune valeur n'a ete lue *i renvoie -1 et la fonction 0;*/