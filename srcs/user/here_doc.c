/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/31 15:56:22 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_write(t_minish *data, int fd, int ignore_expansion, char *input)
{
	char	*expanded_input;

	if (ignore_expansion)
		ft_putstr_fd(input, fd);
	else
	{
		expanded_input = heredoc_expand(data, input);
		if (expanded_input)
		{
			ft_putstr_fd(expanded_input, fd);
			free(expanded_input);
		}
		else
			ft_putstr_fd(input, fd);
	}
	ft_putstr_fd("\n", fd);
}

void	child_heredoc(t_minish *data, char *limiter, int fd, int ignore_expansion)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || ((ft_strncmp(input, limiter, (int)ft_strlen(limiter)) == 0)
        && !input[(int)ft_strlen(limiter)]))
		{
			close(fd);
			break ;
		}
		heredoc_write(data, fd, ignore_expansion, input);
		free(input);
	}
	if (input)
		free(input);
	exit(g_status);
}

void	here_doc(t_minish *data, int *i, int fd)
{
	char	*limiter;
	pid_t	here_doc_pid;
	int		fd_int;
	int		ignore_expansion;
	int		process_status;

	set_signals(HEREDOC);
	fd_int = dup(STDIN_FILENO);
	limiter = getting_rid_of_quotes(data->tokens[*i + 1]);
	ignore_expansion = ft_strlen(data->tokens[*i + 1]) - ft_strlen(limiter);
	g_status = 0;
	here_doc_pid = fork();
	if (here_doc_pid == 0)
		child_heredoc(data, limiter, fd, ignore_expansion);
	close(fd);
	waitpid(here_doc_pid, &process_status, 0);
	g_status = WEXITSTATUS(process_status);
	free(limiter);
	dup2(fd_int, STDIN_FILENO);
}
