/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 16:24:40 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write_bible(t_minish *data, int ignore_exp, char *input)
{
	char	*expanded_input;
	t_list	*tmp;

	tmp = data->aux;
	data->aux = NULL;
	if (ignore_exp)
		ft_lstadd_back(&tmp, ft_lstnew(input));
	else
	{
		expanded_input = heredoc_expand(data, input);
		if (expanded_input)
			ft_lstadd_back(&tmp, ft_lstnew(expanded_input));
		else
			ft_lstadd_back(&tmp, ft_lstnew(input));
	}
	ft_lstadd_back(&tmp, ft_lstnew(ft_strdup("\n")));
	input = NULL;
	data->aux = tmp;
}

void	child_heredoc_bible(t_minish *data, char *lim, int fd, int ignore_exp)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strncmp(input, lim, ft_strlen(lim) + 1) == 0))
		{
			if (!input)
				printf("warning: h-d/l. 1 delimited by eof(wanted `%s')\n", lim);
			break ;
		}
		heredoc_write_bible(data, ignore_exp, input);
	}
	if (input)
		free(input);
	input = make_line_fromlst(&data->aux);
	write(fd, input, ft_strlen(input));
	free(input);
	close(fd);
	exit(g_status);
}

void	here_doc(t_minish *data, int *i, int fd)
{
	char	*lim;
	pid_t	here_doc_pid;
	int		fd_int;
	int		ignore_exp;
	int		process_status;

	set_signals(HEREDOC);
	fd_int = dup(STDIN_FILENO);
	lim = getting_rid_of_quotes(data->tokens[*i + 1]);
	ignore_exp = ft_strlen(data->tokens[*i + 1]) - ft_strlen(lim);
	g_status = 0;
	here_doc_pid = fork();
	if (here_doc_pid == 0)
		child_heredoc_bible(data, lim, fd, ignore_exp);
	close(fd);
	waitpid(here_doc_pid, &process_status, 0);
	g_status = WEXITSTATUS(process_status);
	free(lim);
	dup2(fd_int, STDIN_FILENO);
}
