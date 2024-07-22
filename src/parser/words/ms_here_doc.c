/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:32:02 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/10 18:01:14 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

static int	lim_l(char *lim)
{
	int	inputlen;

	inputlen = ft_strlen(lim);
	return (inputlen);
}

void	ms_write_to_here_doc(t_main *main, char *lim, int filetmp)
{
	char	*line;
	int		error;

	error = 0;
	while (1)
	{
		line = readline("Minishell heredoc> ");
		if (error == GNL_ERROR)
			ms_exit(main, ms_printerror("GNL error\n", strerror(errno), "",
					MS_ERROR_CODE));
		if (!line)
		{
			if (!g_signal)
				ft_putstr_fd("warning: here-document at line 1 delimited by \
				 	end-of-file\n", 1);
			return ;
		}
		if (!ft_strncmp(line, lim, lim_l(lim)) && ft_strlen(line) == lim_l(lim))
			break ;
		ft_putstr_fd(line, filetmp);
		ft_putchar_fd('\n', filetmp);
		free(line);
	}
	if (line)
		free(line);
}

void	ms_here_doc_write(t_main *main, char *lim)
{
	int	filetmp;
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ms_exit(main, ms_printerror("Fork error\n", strerror(errno), "",
				MS_FORK_ERROR));
	if (pid == 0)
	{
		filetmp = open(MS_HERE_DOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0600);
		if (filetmp == -1)
			ms_exit(main, ms_printerror("Permission denied\n", strerror(errno),
					"", MS_PERMISSION));
		signal(SIGINT, ms_sig_handler_hd);
		ms_write_to_here_doc(main, lim, filetmp);
		close(filetmp);
		ms_exit_child(main, 0);
	}
	waitpid(pid, NULL, 0);
	signal(SIGINT, ms_sig_handler);
}

int	ms_here_doc(t_main *main, t_nodlex *tmp, t_nodpars *curpars)
{
	if (tmp->type == here_doc && tmp->next && (tmp->next->type == word
			|| tmp->next->type == dquote || tmp->next->type == squote))
	{
		ms_build_input_node(main, curpars, tmp->next->word, true);
		ms_here_doc_write(main, tmp->next->word);
		tmp->next->type = other;
		return (0);
	}
	else if (tmp->type == here_doc && tmp->next && tmp->next->type == space
		&& tmp->next->next && (tmp->next->next->type == word
			|| tmp->next->next->type == dquote
			|| tmp->next->next->type == squote))
	{
		ms_build_input_node(main, curpars, tmp->next->next->word, true);
		ms_here_doc_write(main, tmp->next->next->word);
		tmp->next->next->type = other;
		return (0);
	}
	else if (tmp->type == here_doc)
		return (1);
	return (0);
}
