/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:52:39 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 16:56:56 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static enum s_tokens	ms_get_token(char c)
{
	if (c == '\'')
		return (squote);
	if (c == '"')
		return (dquote);
	return (-1);
}

static int	ms_check_quotes(t_nodlex *current)
{
	if (current->word[0] == '"' && current->word[ft_strlen(current->word)
			- 1] != '"')
		return (MS_ERROR_DQUOTES);
	else if (current->word[0] == '\'' && current->word[ft_strlen(current->word)
			- 1] != '\'')
		return (MS_ERROR_SQUOTES);
	return (0);
}

int	ms_parsing_quotes(t_main *main, t_piplex *current)
{
	t_nodlex	*tmp;
	char		*strtmp;
	int			res;

	tmp = current->head;
	while (tmp)
	{
		if (tmp->type == word && (tmp->word[0] == '\'' || tmp->word[0] == '"'))
		{
			res = ms_check_quotes(tmp);
			if (res)
				return (res);
			tmp->type = ms_get_token(tmp->word[0]);
			strtmp = ft_substr(tmp->word, 1, ft_strlen(tmp->word) - 2);
			if (!strtmp)
				ms_exit(main, ms_printerror("Malloc error\n", strerror(errno),
						"", MS_ERROR_CODE));
			free(tmp->word);
			tmp->word = strtmp;
		}
		tmp = tmp->next;
	}
	return (0);
}
