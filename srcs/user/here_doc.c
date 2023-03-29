/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/28 16:49:13 by mpagani          ###   ########.fr       */
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

void	here_doc(t_minish *data, int *i, int fd)
{
	char	*input;
	char	*limiter;
	int		fd_int;
	int		ignore_expansion;

	set_signals(HEREDOC);
	fd_int = dup(STDIN_FILENO);
	limiter = getting_rid_of_quotes(data->tokens[*i + 1]);
	ignore_expansion = ft_strlen(data->tokens[*i + 1]) - ft_strlen(limiter);
	g_status = 0;
	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
			break ;
		heredoc_write(data, fd, ignore_expansion, input);
		free(input);
	}
	if (input)
		free(input);
	close(fd);
	dup2(fd_int, STDIN_FILENO);
}
