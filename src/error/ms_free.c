/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:23:29 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 18:09:48 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_lexer(t_main *main)
{
	void	*fstnodes;
	void	*scdnodes;

	while (main->lexer.head)
	{
		fstnodes = main->lexer.head->next;
		while (main->lexer.head->head)
		{
			scdnodes = main->lexer.head->head->next;
			if (main->lexer.head->head->word)
				free(main->lexer.head->head->word);
			free(main->lexer.head->head);
			main->lexer.head->head = scdnodes;
		}
		free(main->lexer.head);
		main->lexer.head = fstnodes;
	}
	main->lexer.size = 0;
}

void	ms_free_out_in(t_nodred *head)
{
	void	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->word)
			free(head->word);
		if (head)
			free(head);
		head = tmp;
	}
}

void	ms_free_parser(t_main *main)
{
	void	*tmp;

	while (main->parser.head)
	{
		tmp = main->parser.head->next;
		if (main->parser.head->args)
			ms_free_var(main->parser.head->args);
		if (main->parser.head->output)
			ms_free_out_in(main->parser.head->output);
		if (main->parser.head->input)
			ms_free_out_in(main->parser.head->input);
		if (main->parser.head->cmd)
			free(main->parser.head->cmd);
		if (main->parser.head->builtin)
			free(main->parser.head->builtin);
		if (main->parser.head->flags)
			ms_free_var(main->parser.head->flags);
		free(main->parser.head);
		main->parser.head = tmp;
	}
	main->parser.size = 0;
}

void	ms_free_path(t_main *main)
{
	if (main->exec.cmdpath)
	{
		free(main->exec.cmdpath);
		main->exec.cmdpath = NULL;
	}
	if (main->exec.path)
	{
		ft_freectab(main->exec.path);
		main->exec.path = NULL;
	}
}

void	ms_free_exec(t_main *main)
{
	if (main->exec.pid)
	{
		free(main->exec.pid);
		main->exec.pid = NULL;
	}
	if (main->exec.pipefd)
	{
		ft_freeiarray(main->exec.pipefd, main->parser.size);
		main->exec.pipefd = NULL;
	}
	if (main->exec.cmdtab)
	{
		ft_freectab(main->exec.cmdtab);
		main->exec.cmdtab = NULL;
	}
	if (main->exec.envptab)
	{
		ft_freectab(main->exec.envptab);
		main->exec.envptab = NULL;
	}
	ms_free_path(main);
}
