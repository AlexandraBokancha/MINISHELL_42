/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:06:15 by eschussl          #+#    #+#             */
/*   Updated: 2024/03/11 15:07:28 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countword(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (c == 0)
		return (1);
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}
