/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:50:10 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 18:04:41 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_var_size(char *str)
{
	int	space;
	int	size;
	int	i;

	i = 0;
	space = 0;
	while (str[i] && str[i] == ' ')
	{
		space++;
		i++;
	}
	while (str[i])
		i++;
	size = i;
	i--;
	while (i >= 0 && str[i] == ' ')
	{
		i--;
		space++;
	}
	if (size > space)
		return (size - space);
	else
		return (0);
}

char	*ms_var_dup(char *str)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	size = ms_var_size(str);
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (!size)
		return (res);
	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (j < size)
		res[j++] = str[i++];
	res[size] = 0;
	return (res);
}

static char	*ms_env_variable(t_main *main, char *str)
{
	t_nodenv	*tmp;
	char		*res;

	tmp = main->envp.head;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->name, ft_strlen(str))
			&& ft_strlen(str) == ft_strlen(tmp->name))
		{
			res = ft_strdup(tmp->value);
			if (!res)
				ms_exit(main, ms_printerror("Malloc error\n", strerror(errno),
						"", MS_ERROR_CODE));
			return (res);
		}
		tmp = tmp->next;
	}
	res = ft_strdup("");
	if (!res)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	return (res);
}

void	ms_expand_var(t_main *main, t_nodlex *tmp)
{
	char		*strtmp;

	strtmp = ms_env_variable(main, &tmp->word[1]);
	free(tmp->word);
	tmp->word = strtmp;
}

void	ms_parsing_env(t_main *main, t_piplex *current)
{
	t_nodlex	*tmp2;
	t_nodlex	*tmp;

	tmp2 = NULL;
	tmp = current->head;
	while (tmp)
	{
		if (tmp->type == word && tmp->word[0] == '$' && (!tmp->word[1]
				|| ft_isdigit(tmp->word[1])) && tmp->next
			&& (tmp->next->type == dquote || tmp->next->type == squote))
			ms_parsing_var_env(tmp, tmp2, current);
		else if ((tmp->type == word || tmp->type == dquote
				|| tmp->type == squote) && tmp->word[0] == '$' && !tmp->word[1])
			ms_parsing_word_env(tmp, main);
		else if ((tmp->type == word || tmp->type == dquote)
			&& tmp->word[0] == '$' && tmp->word[1] == '?')
			ms_parsing_exitcode_env(tmp, main);
		else if ((tmp->type == word || tmp->type == dquote)
			&& tmp->word[0] == '$')
			ms_expand_var(main, tmp);
		tmp = tmp->next;
	}
}
