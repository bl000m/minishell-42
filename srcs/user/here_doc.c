/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 15:13:59 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write_bible(t_minish *data, int ignore_expansion, char *input)
{
	char	*expanded_input;
	t_list	*tmp;

	tmp = data->aux;
	data->aux = NULL;
	if (ignore_expansion)
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

void	child_heredoc_bible(t_minish *data, char *limiter, int fd, int ignore_expansion)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0))
		{
			if (!input)
				printf("minishell: warning: here-document at line 1 \
				delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		heredoc_write_bible(data, ignore_expansion, input);
	}
	if (input)
		free(input);
	input = make_line_fromlst(&data->aux);
	write(fd, input, ft_strlen(input));
	free(input);
	close(fd);
	exit(g_status);
}

// void	heredoc_write(t_minish *data, int fd, int ignore_expansion, char *input)
// {
// 	char	*expanded_input;

// 	if (ignore_expansion)
// 		ft_putstr_fd(input, fd);
// 	else
// 	{
// 		expanded_input = heredoc_expand(data, input);
// 		if (expanded_input)
// 		{
// 			ft_putstr_fd(expanded_input, fd);
// 			free(expanded_input);
// 		}
// 		else
// 			ft_putstr_fd(input, fd);
// 	}
// 	ft_putstr_fd("\n", fd);
// }

// void	child_heredoc(t_minish *data, char *limiter, int fd, int ignore_expansion)
// {
// 	char	*input;

// 	while (1)
// 	{

// 		input = readline("> ");
// 		if (!input || (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0))
// 		{
// 			close(fd);
// 			break ;
// 		}
// 		// buffer = ft_strjoin(buffer, input);
// 		heredoc_write(data, fd, ignore_expansion, input);
// 		free(input);
// 	}
// 	if (input)
// 		free(input);
// 	exit(g_status);
// }

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
		child_heredoc_bible(data, limiter, fd, ignore_expansion);
	close(fd);
	waitpid(here_doc_pid, &process_status, 0);
	g_status = WEXITSTATUS(process_status);
	free(limiter);
	dup2(fd_int, STDIN_FILENO);
}
