/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:10 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 17:09:28 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_new2(t_main *main, t_nodlex *new1, char *rest)
{
	int			i;
	t_nodlex	*new2;

	new2 = ft_calloc(1, sizeof(t_nodlex));
	if (!new2)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	new2->next = new1->next;
	new1->next = new2;
	new2->type = dquote;
	i = 0;
	while (rest[i])
		i++;
	new2->word = ft_calloc(i + 1, sizeof(char));
	if (!new2->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	i = -1;
	while (rest[++i])
		new2->word[i] = rest[i];
}

char	*ms_new0(t_main *main, t_nodlex *current)
{
	int		i;
	char	*res;

	i = 0;
	while (current->word[i] != '$')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (!res)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	i = -1;
	while (current->word[++i] != '$')
		res[i] = current->word[i];
	free(current->word);
	return (res);
}

int	ms_new1_init(t_nodlex *new1, t_nodlex *current, t_main *main)
{
	int	i;
	int	j;

	new1->next = current->next;
	current->next = new1;
	new1->type = dquote;
	i = 0;
	while (current->word[i] != '$')
		i++;
	j = 0;
	while (current->word[i + j] && (ft_isalpha(current->word[i + j])
			|| current->word[i + j] == '_' || (j == 1 && current->word[i
					+ j] == '?') || (j == 0 && current->word[i + j] == '$')
			|| (j > 1 && ft_isdigit(current->word[i + j]))))
		j++;
	new1->word = ft_calloc(j + 1, sizeof(char));
	if (!new1->word)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (i);
}

void	ms_new1(t_main *main, t_nodlex *current)
{
	t_nodlex	*new1;
	int			i;
	int			j;

	new1 = ft_calloc(1, sizeof(t_nodlex));
	if (!new1)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	i = ms_new1_init(new1, current, main);
	j = 0;
	while (current->word[i + j] && (ft_isalpha(current->word[i + j])
			|| current->word[i + j] == '_' || (j == 1 && current->word[i
					+ j] == '?') || (j == 0 && current->word[i + j] == '$')
			|| (j == 0 && current->word[i + j] == '$') || (j > 1
				&& ft_isdigit(current->word[i + j]))))
	{
		new1->word[j] = current->word[i + j];
		j++;
	}
	if (current->word[i + j])
		ms_new2(main, new1, &current->word[i + j]);
}

void	ms_build(t_main *main, t_nodlex *current)
{
	ms_new1(main, current);
	current->word = ms_new0(main, current);
}
