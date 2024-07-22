/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:55:17 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 16:50:10 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser_error(t_piplex *one)
{
	if ((!one->size || (one->size == 1 && one->head->type == space))
		&& one->next)
		return (ms_printerror("syntax error near unexpected token `|'", "", "",
				MS_SYNTAX_ERROR));
	else if (!one->size || (one->size == 1 && one->head->type == space))
		return (ms_printerror("syntax error near unexpected token `newline'",
				"", "", MS_SYNTAX_ERROR));
	return (0);
}

t_nodpars	*ms_init_nodpars(t_main *main, t_nodpars *tmp)
{
	t_nodpars	*new;

	new = ft_calloc(sizeof(t_nodpars), 1);
	if (!new)
		ms_exit(main, ms_printerror("Malloc error\n", strerror(errno), "",
				MS_ERROR_CODE));
	if (!main->parser.head)
		main->parser.head = new;
	else
		tmp->next = new;
	main->parser.size++;
	return (new);
}

static void	ms_parser_no_err(t_main *main, t_piplex *one)
{
	ms_parsingdquotes(main, one);
	ms_parsing_env(main, one);
	ms_parsing_spaces(main, one);
}

int	ms_parser(t_main *main)
{
	t_nodpars	*new;
	t_nodpars	*tmp;
	t_piplex	*one;
	int			res;

	new = NULL;
	one = main->lexer.head;
	if (!main->lexer.head->head && !main->lexer.head->next)
		return (0);
	while (one)
	{
		res = ms_parser_error(one);
		if (res)
			return (res);
		new = ms_init_nodpars(main, tmp);
		res = ms_parsing_quotes(main, one);
		ms_parser_no_err(main, one);
		res = ms_parsing_words(main, one, new);
		if (res)
			return (res);
		one = one->next;
		tmp = new;
	}
	return (0);
}
