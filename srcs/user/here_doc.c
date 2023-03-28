/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/28 16:42:54 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_minish *data, int *i, int fd)
{
	char	*input;
	char	*limiter;
	int		fd_int;

	set_signals(HEREDOC);
	fd_int = dup(STDIN_FILENO);
	limiter = data->tokens[*i + 1];
	g_status = 0;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			// error message and \n
			break ;
		}
		if (!input || (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
		{
			g_status = EXIT_FAILURE;
			close(fd);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
		input = NULL;
	}
	printf("in HEREDOC g_status = %d\n", g_status);
	free(input);
	close(fd);
	dup2(fd_int, STDIN_FILENO);
}
