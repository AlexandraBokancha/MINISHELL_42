/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschussl <eschussl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:42:38 by eschussl          #+#    #+#             */
/*   Updated: 2024/03/10 16:24:19 by eschussl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcheck(char const c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_charcount(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] && ft_charcheck(s1[i], set) == 1)
	{
		count++;
		i++;
	}
	j = ft_strlen(s1) - 1;
	while (j > i && ft_charcheck(s1[j], set) == 1)
	{
		count++;
		j--;
	}
	return (count);
}

static char	*ft_strcpyset(char const *s1, char const *set, char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && ft_charcheck(s1[i], set) == 1)
		i++;
	while (j < len)
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) - ft_charcount(s1, set);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (fd_printf(2, "Error\n"), NULL);
	ft_strcpyset(s1, set, str, len);
	return (str);
}
